#ifndef TELEOP_TASKS1.H;
#define TELEOP_TASKS1.H;

//joystick1 - drive train
//joystick2 - arm & intake

////////////INCLUDE/////////////
#include "teleop_globVars1.h";


/////////////FUNCTIONS//////////////
/* Groups intake motors together
** to run the same power to them
** at the same time. */
void runIntake(int power)
{
	motor[leftIntake] = power;
	motor[rightIntake] = power;
}

/* Groups arm motors together
** to run the same power to them
** at the same time. */
void runArm(int power)
{
	motor[leftArm] = power;
	motor[rightArm] = power;
}

////LOW PRIORITIZATION FUNCTIONS/////
/* Prioritization functions allow one
** driver to override the other based
** set prioritization controls. Each
** function is associated with a task. */

void joy1Arm()
{
	while(true)
	{
		//-----------joystick 1------------//
		//low priority
		getJoystickSettings(joystick);
		if(joy1Btn(6) && !joy1Btn(8)) //move arm up
		{
			runArm(80);
		}
		else if(joy1Btn(8) && !joy1Btn(6)) //move arm down
		{
			runArm(-40);
		}
		else //if not pressed/pressed at same time
		{
			runArm(STOP);
		}
	}
}

void joy2drive()
{
		//-----------joystick 2------------//
		//low priority
		//higher thresholds than joy1
		getJoystickSettings(joystick);
		motor[leftDrive] = abs(joystick.joy2_y1 * 25/32) > DRIVE_HI_THRESH
		? joystick.joy2_y1 * 25/32 //if left movement is significant
		: STOP; //if left movement is insignificant
		motor[rightDrive] = abs(joystick.joy2_y2 * 25/32) > DRIVE_HI_THRESH
		? joystick.joy2_y2 * 25/32 //if right movement is significant
		: STOP; //if right movement is insignificant
}


///////////////TASKS////////////////

///////////////////////////////////////////
//////-------------ARM--------------///////
// Button presses drive motors at set speeds.
// USED: Btn 6 (up), 8 (down)
///////////////////////////////////////////
task Arm()
{
	while(true)
	{
		//-----------joystick 2------------//
		//high priority
		getJoystickSettings(joystick);
		if(joy2Btn(6) && !joy2Btn(8)) //move arm up
		{
			runArm(80);
		}
		else if(joy2Btn(8) && !joy2Btn(6)) //move arm down
		{
			runArm(-40);
		}
		else //if not pressed/pressed at same time
		{
			//joy1Arm();
			runArm(STOP);
		}
	}
}


///////////////////////////////////////////
//////---------DRIVE TRAIN----------///////
// Direct tank drive to motors.
// USED: joysticks (speed and direction)
///////////////////////////////////////////
task DriveTrain()
{
	while(true)
	{
		//high priority
		//-----------joystick 1------------//
		getJoystickSettings(joystick);
		if(abs(joystick.joy1_y1 * 25/32) > DRIVE_LOW_THRESH || abs(joystick.joy1_y2 * 25/32) > DRIVE_LOW_THRESH)
		//if movement is significant
		{
			motor[leftDrive] = joystick.joy1_y1 * 25/32;
			motor[rightDrive] = joystick.joy1_y2 *25/32;
		}
		else //if movement is insignificant
		{
			joy2drive();
		}
	}
}


///////////////////////////////////////////
//////-------------HANG-------------///////
// Button presses drive motors at set speeds.
// USED: Btn 1 (FS, Raise), TopHat 0 (D-UP, FS, Lift)
///////////////////////////////////////////
task Hang()
{
	while(true)
	{
		getJoystickSettings(joystick);
		//Activates winch lift motors
		if(joy1Btn(7) && joy2Btn(7))
		{
			motor[hang1] = MOT_MAX;
			motor[hang2] = MOT_MAX;
		}
		else
		{
			motor[hang1] = STOP;
			motor[hang2] = STOP;
		}
		//Only when the button for the lift arms are pressed, lift
		if(joy1Btn(1) && joy2Btn(1))
		{
			servoTarget[hangServo1] = 250;
			servoTarget[hangServo2] = 0;
		}
		//Otherwise, Drop the servo arms
		else
		{
			servoTarget[hangServo1] = 90;
			servoTarget[hangServo2] = 160;
		}
	}
}


///////////////////////////////////////////
//////------------INTAKE------------///////
// Button presses drive motors at set speeds.
// USED: Btn 5 (eat/drop), Btn 2 (Toggle Intake)
///////////////////////////////////////////
task Intake()
{
	bool toggle = false;
	while(true)
	{
		getJoystickSettings(joystick);
		//Activates Servo Drop and Returns Servo to Initial Position
		servoTarget[intakeServo] = joy2Btn(5)
		? 150
		: 80;
		if(joy2Btn(2))
		{
			toggle = !toggle;
			wait10Msec(25);
		}
		if(toggle)
		{
			runIntake(100);
		}
		else
		{
			runIntake(0);
		}
	}
}


//----NOT TO BE USED FOR COMPETITION 1---//

///////////////////////////////////////////
//////----------TURNTABLE-----------///////
// D-pad drives motor at set speed.
// USED: TopHat 2 (right), TopHat 4 (left)
//       Btn 5 (set slow speed)
///////////////////////////////////////////
/*task Turntable()
{
	while(true)
	{
		getJoystickSettings(joystick);

		//-----------joystick 1------------//
		//low priority
		if(joystick.joy1_TopHat == 2 && !(joystick.joy1_TopHat == 4)) //turntable right
		{
			if(!joy2Btn(5)) //regular speed
			{
				motor[tableMotor] = TABLE_HI_POW;
			}
			else //slow speed
			{
				motor[tableMotor] = TABLE_LOW_POW;
			}
		}
		else //if no top hat input
		{
			motor[tableMotor] = STOP;
		}
		if(joystick.joy1_TopHat == 4 && !(joystick.joy1_TopHat == 2)) //turntable left
		{
			if(!joy2Btn(5)) //regular speed
			{
				motor[tableMotor] = TABLE_HI_POW;
			}
			else //slow speed
			{
				motor[tableMotor] = TABLE_LOW_POW;
			}
		}
		else //if no top hat input
		{
			motor[tableMotor] = STOP;
		}

		//-----------joystick 2------------//
		//high priority
		if(joystick.joy2_TopHat == 2 && !(joystick.joy2_TopHat == 6)) //turntable right
		{
			if(!joy2Btn(5)) //regular speed
			{
				motor[tableMotor] = TABLE_HI_POW;
			}
			else //slow speed
			{
				motor[tableMotor] = TABLE_LOW_POW;
			}
		}
		else //if no top hat input
		{
			motor[tableMotor] = STOP;
		}

		if(joystick.joy2_TopHat == 6 && !(joystick.joy2_TopHat == 2)) //turntable left
		{
			if(!joy2Btn(5)) //regular speed
			{
				motor[tableMotor] = -TABLE_HI_POW;
			}
			else //slow speed
			{
				motor[tableMotor] = -TABLE_LOW_POW;
			}
		}
		else //if no top hat input
		{
			motor[tableMotor] = STOP;
		}
	}
}*/



#endif;
