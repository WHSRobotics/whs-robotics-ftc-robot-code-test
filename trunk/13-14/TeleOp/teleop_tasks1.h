#ifndef TELEOP_TASKS1.H;
#define TELEOP_TASKS1.H;

//joystick1 - drive train & intake
//joystick2 - arm & turntable

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
		getJoystickSettings(joystick);
		//-----------joystick 1------------//
		//low priority
		if(joy1Btn(6) && !joy1Btn(8)) //move arm up
		{
			runArm(MOT_MAX);
		}
		else //if not pressed/pressed at same time
		{
			runArm(STOP);
		}
		if(joy1Btn(8) && !joy1Btn(6)) //move arm down
		{
			runArm(-MOT_MAX);
		}
		else //if not pressed/pressed at same time
		{
			runArm(STOP);
		}

		//-----------joystick 2------------//
		//high priority
		if(joy2Btn(6) && !joy2Btn(8)) //move arm up
		{
			runArm(MOT_MAX);
		}
		else //if not pressed/pressed at same time
		{
			runArm(STOP);
		}
		if(joy2Btn(8) && !joy2Btn(6)) //move arm down
		{
			runArm(-MOT_MAX);
		}
		else //if not pressed/pressed at same time
		{
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
		getJoystickSettings(joystick);

		//-----------joystick 1------------//
		//high priority
		if(abs(joystick.joy1_y1) > DRIVE_LOW_THRESH) //if left movement is significant
		{
			motor[leftDrive] = joystick.joy1_y1;
		}
		else //if left movement is insignificant
		{
			motor[leftDrive] = STOP;
		}
		if(abs(joystick.joy1_y2) > DRIVE_LOW_THRESH) //if right movement is significant
		{
			motor[rightDrive] = joystick.joy1_y2;
		}
		else //if right movement is insignificant
		{
			motor[rightDrive] = STOP;
		}

		//-----------joystick 2------------//
		//low priority
		//higher thresholds than joy1
		if(abs(joystick.joy2_y1) > DRIVE_HI_THRESH) //if left movement is significant
		{
			motor[leftDrive] = joystick.joy2_y1;
		}
		else //if left movement is insignificant
		{
			motor[leftDrive] = STOP;
		}

		if(abs(joystick.joy2_y2) > DRIVE_HI_THRESH) //if right movement is significant
		{
			motor[rightDrive] = joystick.joy2_y2;
		}
		else //if right movement is insignificant
		{
			motor[rightDrive] = STOP;
		}
	}
}



///////////////////////////////////////////
//////-------------HANG-------------///////
// Button presses drive motors at set speeds.
// USED: Btn 1 (up), Btn 3 (down)
///////////////////////////////////////////
task Hang()
{
	while(true)
	{
		getJoystickSettings(joystick);

		//-----------joystick 1------------//
		//high priority
		if(joy1Btn(1) && !joy1Btn(3)) //go up
		{
			motor[hangMotor] = MOT_MAX;
		}
		else //if not pressed/pressed same time
		{
			motor[hangMotor] = STOP;
		}
		if(joy1Btn(3) && !joy1Btn(1)) //go down
		{
			motor[hangMotor] = -MOT_MAX;
		}
		else //if not pressed/pressed same time
		{
			motor[hangMotor] = STOP;
		}

		//-----------joystick 2------------//
		//low priority
		if(joy2Btn(1) && !joy2Btn(3)) //go up
		{
			motor[hangMotor] = MOT_MAX;
		}
		else //if not pressed/pressed same time
		{
			motor[hangMotor] = STOP;
		}
		if(joy2Btn(3) && !joy2Btn(1)) //go down
		{
			motor[hangMotor] = -MOT_MAX;
		}
		else //if not pressed/pressed same time
		{
			motor[hangMotor] = STOP;
		}
	}
}


///////////////////////////////////////////
//////------------INTAKE------------///////
// Button presses drive motors at set speeds.
// USED: Btn 2 (eat), Btn 4 (cough)
///////////////////////////////////////////
task Intake()
{
	while(true)
	{
		getJoystickSettings(joystick);

		//-----------joystick 1------------//
		//high priority
		if(joy1Btn(2) && !joy1Btn(4)) //eat waffles
		{
			runIntake(INTAKE_POW);
		}
		else //if not pressed/pressed at same time
		{
			runIntake(STOP);
		}
		if(joy1Btn(4) && !joy1Btn(2)) //cough waffles
		{
			runIntake(-INTAKE_POW);
		}
		else //if not pressed/pressed at same time
		{
			runIntake(STOP);
		}

		//-----------joystick 2------------//
		//low priority
		if(joy2Btn(2) && !joy2Btn(4)) //eat waffles
		{
			runIntake(INTAKE_POW);
		}
		else //if not pressed/pressed at same time
		{
			runIntake(STOP);
		}
		if(joy2Btn(4) && !joy2Btn(2)) //cough waffles
		{
			runIntake(-INTAKE_POW);
		}
		else //if not pressed/pressed at same time
		{
			runIntake(STOP);
		}
	}
}



///////////////////////////////////////////
//////----------TURNTABLE-----------///////
// D-pad drives motor at set speed.
// USED: TopHat 2 (right), TopHat 4 (left)
//       Btn 5 (set slow speed)
///////////////////////////////////////////
task Turntable()
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
}



#endif;
