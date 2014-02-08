#ifndef TELEOP_TASKS4-SW.H;
#define TELEOP_TASKS4-SW.H;

/*
winch = dc motor
flag = dc motor
velcro = nxt motor
intake = 2 nxt motors
turntable = dc motor
ratchetDisable = servo
*/


#include "all_joy_driver.h"


////////////////ANI CONTROLS////////////////
void runIntake(float motPow)
{
	motor[intakeL] = motPow;
	motor[intakeR] = motPow;
}

void runArm(float motPow)
{
	motor[armL] = motPow;
	motor[armR] = motPow;
}



/**********SCORING ARM********
1 DC Motor
ANI Controlled
Btn 6 = raise arm
Btn 8 = lower arm
*****************************/
task Arm()
{
	while(true)
	{
		getJoystickSettings(joystick);

		if((ANIjoy2 && joy2Btn(6) && !joy2Btn(8)) || (!DTjoy1 && joy1Btn(6) && !joy1Btn(8)))
		{
			//raise arm
			runArm(ARM_UP);
			if(intakeOn) //if intake is on
			{
				intakeReversed = true; //intake reversed to keep cubes in
			}
		}
		else if((ANIjoy2 && joy2Btn(8) && !joy2Btn(6)) || (!DTjoy1 && joy1Btn(8) && !joy1Btn(6)))
		{
			//lower arm
			runArm(ARM_DOWN);
			//-/writeDebugStreamLine("arm motor -50");
			if(intakeReversed)
			{
				intakeReversed = false;
			}
		}
		else
		{
			//don't run arm
			runArm(STOP);
			if(intakeReversed)
			{
				intakeReversed = false;
			}
		}
	}
}



/***********INTAKE***********
2 NXT motors
ANI Controlled
Btn 2: Intake Toggle
Btn 5: Dropbox Open
*****************************/
task Intake()
{
	while(true)
	{
		getJoystickSettings(joystick);

		if(ANIjoy2 && getTap(2,2) || !DTjoy1 && getTap(1,2))
		{
			intakeOn = !intakeOn;
			/*//-/if(intakeOn)
				writeDebugStreamLine("intake on");
			else
				writeDebugStreamLine("intake off");*/
		}
		if(ANIjoy2 && getTap(2,5) || !DTjoy1 && getTap(1,5))
		{
			boxOpen = !boxOpen;
			/*//-/if(boxOpen)
				writeDebugStreamLine("box open");
			else
				writeDebugStreamLine("box closed");*/
		}

		if(intakeOn)
		{
			if(intakeReversed)
				runIntake(INTAKE_R);
			else
				runIntake(MAX);
		}
		else
		{
			runIntake(STOP);
		}

		if(boxOpen)
		{
			servo[dropbox] = BOX_OPEN;
		}
		else
		{
			servo[dropbox] = BOX_CLOSED;
		}
	}
}



////////////////////DT CONTROLS////////////////////
//////////FUNCTIONS//////////////
int getActiveDTJoy(bool tank)
{
	bool j1_active = ((abs(joystick.joy1_x1) > IDLE_THRESH) || (abs(joystick.joy1_x2) > IDLE_THRESH) || (abs(joystick.joy1_y1) > IDLE_THRESH) || (abs(joystick.joy1_y2) > IDLE_THRESH));
	bool j2_active = ((abs(joystick.joy2_x1) > IDLE_THRESH) || (abs(joystick.joy2_x2) > IDLE_THRESH) || (abs(joystick.joy2_y1) > IDLE_THRESH) || (abs(joystick.joy2_y2) > IDLE_THRESH));
	if(tank)
	{
		/* Cases in order of priority:
		1: 1 DT control and is not idle.  DT control is active.
		2: 1 DT control and is idle.  ANI control is active.
		3: 2 DT controls, 1 is idle.  !idle is active.
		4: 2 DT controls, 2 are idle.  none are active.
		5: 2 DT controls, 2 are not idle.  joy1 is active.
		6: 0 DT controls.  none are active.
		*/
		if((DTjoy1 && j1_active) || (!ANIjoy2 && !j2_active) || (j1_active && j2_active))
		{
			return 1;
		}
		else if((DTjoy1 && !j1_active) || (!ANIjoy2 && j2_active))
		{
			return 2;
		}
		else if(DTjoy1 && !ANIjoy2)
		{
			if(j1_active)
				return 1;
			else if(j2_active)
				return 2;
			else
				return 0;
		}
		else
		{
			return 0;
		}
	}
	else //swerve drive active
	{
		/* Cases in order of priority:
		1: 1 DT control and is not idle.  DT control is active.
		2: 1 DT control and is idle.  none are active.
		3: 2 DT controls, 1 is idle.  !idle is active.
		4: 2 DT controls, 2 are idle.  none are active.
		5: 2 DT controls, 2 are not idle.  joy1 is active.
		6: 0 DT controls.  none are active.
		*/
		if((DTjoy1 && j1_active) || (j1_active && j2_active))
		{
			return 1;
		}
		else if(!ANIjoy2 && j2_active)
		{
			return 2;
		}
		else if(DTjoy1 && !ANIjoy2)
		{
			if(j1_active)
				return 1;
			else if(j2_active)
				return 2;
			else
				return 0;
		}
		else
		{
			return 0;
		}
	}
}

float magnitudeCalc(float inputX, float inputY)
{
	return sqrt( pow(inputX, 2) + pow(inputY, 2) ) < 128.0
	? sqrt( pow(inputX, 2) + pow(inputY, 2) )
	: 128.0;
}

float piMotorOnly(float inputY, float inputX)
{
	if(atan2(inputY, inputX) < 0)
	{
		return -magnitudeCalc(inputY, inputX) * JOY_MAP;
	}
	else
	{
		return magnitudeCalc(inputY, inputX)* JOY_MAP;
	}
}

void piMotor(tMotor motorName, TServoIndex servoName, float inputY, float inputX, int initServoPos)
{
	if((magnitudeCalc(inputY, inputX) > LOW_THRESH) && (magnitudeCalc(inputY, inputX) <= 128.0))
	{
		if(atan2(inputY, inputX) < 0)
		{
			servo[servoName] = (atan2(inputY, inputX) + PI) * SERVO_MAP + initServoPos;
			motor[motorName] = -magnitudeCalc(inputY, inputX) * JOY_MAP;
		}
		else
		{
			servo[servoName] = atan2(inputY, inputX) * SERVO_MAP + initServoPos;
			motor[motorName] = magnitudeCalc(inputY, inputX)* JOY_MAP;
		}
	}
	else
	{
		servo[servoName] = PI/2.0 * SERVO_MAP + initServoPos;
		motor[motorName] = 0;
	}
}

void assistedTankControl(float diffY1Input, float diffY2Input)
{
	float scaledY1 = -diffY1Input * TANK_SPEED_SCALE;
	float scaledY2 = -diffY2Input * TANK_SPEED_SCALE;
	float velX = HALF_LENGTH_Y * (scaledY1 - scaledY2)/(2.0*HALF_WIDTH_X);

	piMotor(sweFL, swiFL, scaledY1, -velX, 0);
	piMotor(sweBL, swiBL, scaledY1, velX, -20);
	piMotor(sweFR, swiFR, scaledY2, -velX, 0);
	piMotor(sweBR, swiBR, scaledY2, velX, 0);
}

void swerveControl(float transYInput, float transXInput, float angularInput)
{
	float angSclr;
	if(magnitudeCalc(transXInput, transYInput) > LOW_THRESH)
	{
		angSclr = angularInput * ROT_SCALE;
	}
	else if(abs(angularInput) > HI_THRESH)
	{
		angSclr = angularInput * ROT_ONLY_SCALE;
	}
	else
	{
		angSclr = 0.0;
	}
	float transXSclr = magnitudeCalc(transXInput, transYInput) > LOW_THRESH
	? transXInput * SWERVE_SPEED_SCALE
	: 0.0 ;
	float transYSclr = magnitudeCalc(transXInput, transYInput) > LOW_THRESH
	? -transYInput * SWERVE_SPEED_SCALE
	: 0.0 ;

	float velFLX = transXSclr - (angSclr * HALF_LENGTH_Y);
	float velFLY = transYSclr - (angSclr * HALF_WIDTH_X);

	float velBLX = transXSclr + (angSclr * HALF_LENGTH_Y);
	float velBLY = transYSclr - (angSclr * HALF_WIDTH_X);

	float velFRX = transXSclr - (angSclr * HALF_LENGTH_Y);
	float velFRY = transYSclr + (angSclr * HALF_WIDTH_X);

	float velBRX = transXSclr + (angSclr * HALF_LENGTH_Y);
	float velBRY = transYSclr + (angSclr * HALF_WIDTH_X);

	piMotor(sweFL, swiFL, velFRY, velFRX, 0);
	piMotor(sweBL, swiBL, velBRY, velBRX, -20);
	piMotor(sweFR, swiFR, velFLY, velFLX, 0);
	piMotor(sweBR, swiBR, velBLY, velBLX, 0);
	//-/writeDebugStreamLine("sweFL: %f, sweBL: %f, sweFR: %f, sweBR: %f", piMotorOnly(velFLY, velFLX), piMotorOnly(velBLY, velBLX), piMotorOnly(velFRY,velFRX), piMotorOnly(velBRY, velBLX));
}


/*******DRIVE CONTROL********
Btn 6: Tank Drive Active
Btn 5: Swerve Drive Active
*****************************/
task DriveControl()
{
	while(true)
	{
		getJoystickSettings(joystick);
		if((joy1Btn(6) && DTjoy1 && !joy1Btn(5)) || (!ANIjoy2 && joy2Btn(6) && !joy2Btn(5)))
		{
			tankDrive = true; //tank drive active
			//-/writeDebugStreamLine("tank drive on");
		}
		else if((joy1Btn(5) && DTjoy1 && !joy1Btn(6)) || (joy2Btn(5) && !ANIjoy2 && !joy2Btn(6)))
		{
			tankDrive = false; //swerve drive active
			//-/writeDebugStreamLine("tank drive off");
		}

		if(tankDrive) //tank drive active
		{
			if(getActiveDTJoy(true) == 1)
			{
				assistedTankControl(joystick.joy1_y1, joystick.joy1_y2);
				//-/writeDebugStreamLine("tank joy1");
			}
			else
			{
				assistedTankControl(joystick.joy2_y1, joystick.joy2_y2);
				//-/writeDebugStreamLine("tank joy2");
			}
		}
		else //swerve drive active
		{
			if(getActiveDTJoy(false) == 1)
			{
				swerveControl(joystick.joy1_y1, joystick.joy1_x1, joystick.joy1_x2);
				//-/writeDebugStreamLine("swerve joy1");
			}
			else if(ANIjoy2)
			{
				assistedTankControl(joystick.joy2_y1, joystick.joy2_y2);
				//-/writeDebugStreamLine("tank joy2");
			}
			else
			{
				swerveControl(joystick.joy2_y1, joystick.joy2_x1, joystick.joy2_x2);
				//-/writeDebugStreamLine("swerve joy2");
			}
		}
	}
}



/****************************
//SWERVE DRIVE CODE HERE
*****************************/


//////////////UNUSED CODE////////////////
//Turntable variables
/*bool posMove = false; //check if positive turn can be made
bool negMove = false; //check if negative turn can be made
bool lowPowBtn = false;
bool hiPowBtn = false;
const float ENCODER2TT = 1.0/6.0; //ratio of turntable to motor encoder revolutions
int currPow = 100;*/

/*void runTurntable(int joy)
{
	getJoystickSettings(joystick);
	posMove = (getTopHat(joy, 2) && nMotorEncoder[ttMot] <= 90*ENCODER2TT);
	negMove = (getTopHat(joy, 6) && nMotorEncoder[ttMot] >= -90*ENCODER2TT);
	lowPowBtn = getTopHat(joy, 4);
	hiPowBtn = getTopHat(joy, 0);

	if(hiPowBtn && !lowPowBtn)
	{
		currPow = 50;
	}
	else if(lowPowBtn)
	{
		currPow = 20;
	}


	if(posMove) //if significant movement detected and limited by angle
	{
		writeDebugStreamLine("turntable %f", currPow);
		///motor[ttMot] = currPow; //set motor power proportional to joystick value
	}
	else if(negMove)
	{
		writeDebugStreamLine("turntable %f", -currPow);
		///motor[ttMot] = -currPow;
	}
	else //if no significant movement or outside angle limits
	{
		///motor[ttMot] = 0; //do not move motor
	}

	///writeDebugStreamLine("%f", nMotorEncoder[ttMot]);
}
*/


/*********TURNTABLE*********
DC Motor
ANI Controlled
D-Pad L and R: Turntable Direction
D-Pad U and D: High/Low Power
*****************************/
/*task Turntable()
{
	nMotorEncoder[ttMot] = 0; //reset motor encoder

	while(true)
	{
		if(ANIjoy2)
		{
			runTurntable(2);
		}
		else if(!DTjoy1)
		{
			runTurntable(1);
		}

		///writeDebugStreamLine("%f", nMotorEncoder[ttMot]);
	}
}
*/


#endif
