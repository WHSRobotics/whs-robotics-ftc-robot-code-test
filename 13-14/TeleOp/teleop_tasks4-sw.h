/*
winch = dc motor
flag = dc motor
velcro = nxt motor
intake = 2 nxt motors
turntable = dc motor
ratchetDisable = servo
*/

#include "JoystickDriver.c"

const int HI_THRESH = 25;
const int LOW_THRESH = 15;
const float JOY_MAP = 0.78125;
const float SERVO_MAP = 255.0/PI;
const float ROT_SCALE = 0.075;
const float TANK_SPEED_SCALE = 1.0;
const float SWERVE_SPEED_SCALE = 1.0;
const float HALF_WIDTH_X = 6.8125;
const float HALF_LENGTH_Y = 7.125;

bool intakeOn = false;
bool intakeReversed = false;

/*
void runIntake(float motPow)
{
	motor[intakeL] = motPow;
	motor[intakeR] = motPow;
}*/

////////----FUNCTIONS----////////

float magnitudeCalc(float inputX, float inputY)
{
	return sqrt( pow(inputX, 2) + pow(inputY, 2) ) < 128.0
	? sqrt( pow(inputX, 2) + pow(inputY, 2) )
	: 128.0;
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
	piMotor(sweBL, swiBL, scaledY1, velX, 0);
	piMotor(sweFR, swiFR, scaledY2, -velX, 0);
	piMotor(sweBR, swiBR, scaledY2, velX, 0);
}

void swerveControl(float transYInput, float transXInput, float angularInput)
{
	float angSclr = abs(angularInput) > HI_THRESH
	? angularInput * ROT_SCALE
	: 0.0 ;
	float transXSclr = magnitudeCalc(transXInput, transYInput) > LOW_THRESH
	? transXInput * SWERVE_SPEED_SCALE
	: 0.0 ;
	float transYSclr = magnitudeCalc(transXInput, transYInput) > LOW_THRESH
	? transYInput * SWERVE_SPEED_SCALE
	: 0.0 ;

	float velFLX = angSclr * -HALF_LENGTH_Y + transXSclr;
	float velFLY = angSclr * -HALF_WIDTH_X + transYSclr;

	float velBLX = angSclr * HALF_LENGTH_Y + transXSclr;
	float velBLY = angSclr * -HALF_WIDTH_X +  transYSclr;

	float velFRX = angSclr * -HALF_LENGTH_Y + transXSclr;
	float velFRY = angSclr * HALF_WIDTH_X +  transYSclr;

	float velBRX = angSclr * HALF_LENGTH_Y + transXSclr;
	float velBRY = angSclr * HALF_WIDTH_X + transYSclr;

	piMotor(sweFL, swiFL, -velFLY, velFLX, 0);
	piMotor(sweBL, swiBL, -velBLY, velBLX, 0);
	piMotor(sweFR, swiFR, -velFRY, velFRX, 0);
	piMotor(sweBR, swiBR, -velBRY, velBRX, 0);
}

void driveSwitch()
{
	bool toggle = true;
	while(true)
	{
		getJoystickSettings(joystick);
		if(joy1Btn(9))
		{
			toggle = !toggle;
			wait10Msec(25);
		}
		if(toggle)
		{
			swerveControl(joystick.joy1_y1, joystick.joy1_x1, joystick.joy1_x2);
		}
		else
		{
			assistedTankControl(joystick.joy1_y1, joystick.joy1_y2);
		}
	}
}

////////----TASKS----////////

/**********DRIVE TRAIN********
Controls 4 Servos and 4 Motors
Joystick 1 and 2
Btn 9 = toggle drive style
*****************************/
task Drivetrain()
{
	driveSwitch();
}

/**********SCORING ARM********
Powered by 1 DC Motor
Joystick 2
Btn 6 = raise arm
Btn 8 = lower arm
*****************************/
task Arm()
{
	bool armRaise = false;
	bool armLower = false;

	while(true)
	{
		getJoystickSettings(joystick);

		armRaise = (joy2Btn(6) && !joy2Btn(8));
		armLower = (joy2Btn(8) && !joy2Btn(6));

		if(armRaise)
		{
			//raise arm
			motor[armMot] = 90;
			if(intakeOn) //if intake is on
			{
				intakeReversed = true; //intake reversed to keep cubes in
			}
		}
		else if(armLower)
		{
			//lower arm
			motor[armMot] = -50;
			if(intakeReversed)
			{
				intakeReversed = false;
			}
		}
		else
		{
			//don't run arm
			motor[armMot] = 0;
			if(intakeReversed)
			{
				intakeReversed = false;
			}
		}
	}
}


/************HANG*************
FAILSAFE ACTIVE
Hold down btn 4: Open servo
Hold down btn 1: Activate hangman
*****************************/
task Hang()
{
	bool winchForward = false;
	bool winchBackward = false;
	bool hangmanOn = false;

	while(true)
	{
		getJoystickSettings(joystick);
		//Check conditions
		winchForward = (joy1Btn(7) && joy2Btn(7));
		winchBackward = (joy1Btn(4) && joy2Btn(4));
		hangmanOn = (joy1Btn(1) && joy2Btn(1));

		/*
		//Hangman movement
		if(hangmanOn)
		{
			motor[hangmanMot] = 90;
		}
		else
		{
			motor[hangmanMot] = 0;
		}
		*/
		//Winch & Anti-ratchet movement
		if(winchForward && !winchBackward)
		{
			motor[winchMot] = 100;
		}
		else if(winchBackward)
		{
			motor[winchMot] = -100;
			servo[antiRatchet] = 255; //open
		}
		else
		{
			motor[winchMot] = 0;
			servo[antiRatchet] = 90; //closed
		}
	}
}


/************FLAG*************
FAILSAFE ACTIVE
Btn 3 simultaneously pressed on
both joysticks runs a
DC Motor at +100 power.
*****************************/
task Flag()
{
	bool flagOn = false;
	while(true)
	{
		getJoystickSettings(joystick);
		//Check conditions
		flagOn = (joy1Btn(3) && joy2Btn(3));

		if(flagOn)
		{
			motor[flagMot] = 100;
		}
		else
		{
			motor[flagMot] = 0;
		}
	}
}


/***********INTAKE***********
2 NXT motors
Joystick 2
Btn 2: Intake Toggle
*****************************/
/*task Intake()
{
	bool toggleNeeded = false;
	while(true)
	{
		getJoystickSettings(joystick);
		toggleNeeded = joy1Btn(2);

		if(toggleNeeded)
		{
			intakeOn = !intakeOn;
		}

		if(intakeOn)
		{
			if(intakeReversed)
				runIntake(-50);
			else
				runIntake(100);
		}
		else
		{
			runIntake(0);
		}
	}
}
*/

/*********TURNTABLE*********
D-Pad left and right on joy2
run a DC motor accordingly
*****************************/
task Turntable()
{
	const float ENCODER2TT = 1.0/6.0; //ratio of turntable to motor encoder revolutions
	//const float JOY2POW = 100.0/128.0; //convert joystick value to motor power
	//const int JOY_THRESH = 10; //joystick threshold for dead zone
	int currPow = 100;
	nMotorEncoder[ttMot] = 0; //reset motor encoder
	//Check conditions
	bool posMove = false; //check if positive turn can be made
	bool negMove = false; //check if negative turn can be made
	bool lowPowBtn = false;
	bool hiPowBtn = false;

	while(true)
	{
		getJoystickSettings(joystick);
		posMove = (joystick.joy2_TopHat == 2 && nMotorEncoder[ttMot] <= 90*ENCODER2TT);
		negMove = (joystick.joy2_TopHat == 6 && nMotorEncoder[ttMot] >= -90*ENCODER2TT);
		lowPowBtn = (joystick.joy2_TopHat == 4);
		hiPowBtn = (joystick.joy2_TopHat == 0);

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
			motor[ttMot] = currPow; //set motor power proportional to joystick value
		}
		else if(negMove)
		{
			motor[ttMot] = -currPow;
		}
		else //if no significant movement or outside angle limits
		{
			motor[ttMot] = 0; //do not move motor
		}

		writeDebugStreamLine("%f", nMotorEncoder[ttMot]);
	}
}