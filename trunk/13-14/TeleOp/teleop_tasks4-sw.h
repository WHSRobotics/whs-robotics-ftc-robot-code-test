/*
winch = dc motor
flag = dc motor
velcro = nxt motor
intake = 2 nxt motors
turntable = dc motor
ratchetDisable = servo
*/

#include "JoystickDriver.c"

bool intakeOn = false;
bool intakeReversed = false;


/*
void runIntake(float motPow)
{
	motor[intakeL] = motPow;
	motor[intakeR] = motPow;
}*/


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
