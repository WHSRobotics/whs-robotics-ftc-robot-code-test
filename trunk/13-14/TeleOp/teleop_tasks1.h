#ifndef TELEOP_TASKS1.H;
#define TELEOP_TASKS1.H;

//joystick1 - drive train & intake
//joystick2 - arm & turntable

//---------INCLUDE----------
#include "teleop_globVars1.h";


/////////////TASKS//////////////
task DriveTrain()
{
	while(true)
	{
		getJoystickSettings(joystick);
		/////////////JOYSTICK 1/////////////
		//high priority
		if(abs(joystick.joy1_y1) > DRIVE_LOW_THRESH)
		{
			motor[leftDrive] = joystick.joy1_y1;
		}
		else
		{
			motor[leftDrive] = STOP;
		}
		if(abs(joystick.joy1_y2) > DRIVE_LOW_THRESH)
		{
			motor[rightDrive] = joystick.joy1_y2;
		}
		else
		{
			motor[rightDrive] = STOP;
		}

		/////////////JOYSTICK 2//////////////
		//low priority
		//higher thresholds than joy1
		if(abs(joystick.joy2_y1) > DRIVE_HI_THRESH)
		{
			motor[leftDrive] = joystick.joy2_y1;
		}
		else
		{
			motor[leftDrive] = STOP;
		}

		if(abs(joystick.joy2_y2) > DRIVE_HI_THRESH)
		{
			motor[rightDrive] = joystick.joy2_y2;
		}
		else
		{
			motor[rightDrive] = STOP;
		}
	}
}


task Arm()
{
	while(true)
	{
		getJoystickSettings(joystick);

		/////////////JOYSTICK1//////////////
		//low priority


		/////////////JOYSTICK 2/////////////
		//high priority
		if(joy2Btn(6) && !joy2Btn(8)) //raise arm
		{
			//servo[armServo] =
		}
		else
		{
			//code here
		}

		if(joy2Btn(8) && !joy2Btn(6)) //lower arm
		{
			//servo[armServo] =
		}
		else
		{
			//code here
		}

	}
}


task Turntable()
{
	while(true)
	{
		getJoystickSettings(joystick);

		////////////////////JOYSTICK 1//////////////////
		//low priority
		if(joy1_TopHat == 2)
		{
		motor[tableMotor] = 100;
		}
		if(joy1_TopHat == 4)
		{
			motor[tableMotor] = -100;
		}
		else
		{
			motor[tableMotor] = 0;
		}

		//////////////////JOYSTICK 2/////////////////
		//high priority
		if(joystick.joy2_TopHat == 2 && !(joystick.joy2_TopHat == 6)) //turntable right
		{
			if(!joy2Btn(5)) //regular speed
			{
				motor[tableMotor] = TABLE_HI_POW;
			}
			else //slow
			{
				motor[tableMotor] = TABLE_LOW_POW;
			}
		}
		else //if not pressed
		{
			motor[tableMotor] = STOP;
		}

		if(joystick.joy2_TopHat == 6 && !(joystick.joy2_TopHat == 2)) //turntable left
		{
			if(!joy2Btn(5)) //regular speed
			{
				motor[tableMotor] = -TABLE_HI_POW;
			}
			else //slow
			{
				motor[tableMotor] = -TABLE_LOW_POW;
			}
		}
		else //if not pressed
		{
			motor[tableMotor] = STOP;
		}
	}
}


task Hang()
{
	while(true)
	{
		getJoystickSettings(joystick);

		/////////////JOYSTICK 1/////////////
		//high priority
		if(joy1Btn(1))
		{
			motor[hangMotor] = 100;
		}
		if(joy1Btn(3))
		{
			motor[hangMotor] = -100;
		}
		else
		{
			motor[hangMotor] = 0;
		}

		////////////JOYSTICK 2/////////////
		//low priority
		if(joy2Btn(1))
		{
			motor[hangMotor] = 100;
		}
		if(joy2Btn(3))
		{
			motor[hangMotor] = -100;
		}
		else
		{
			motor[hangMotor] = 0;
		}
	}
}


void runIntake(int power)
{
	motor[leftIntake] = power;
	motor[rightIntake] = power;
}


task Intake()
{
	while(true)
	{
		getJoystickSettings(joystick);

		//////////////JOYSTICK 2////////////
		//low priority
		if(joy2Btn(2) && !joy2Btn(4)) //eat waffles
		{
			runIntake(INTAKE_POW);
		}
		else
		{
			runIntake(STOP);
		}
		if(joy2Btn(4) && !joy2Btn(2)) //cough waffles
		{
			runIntake(-INTAKE_POW);
		}
		else
		{
			runIntake(STOP);
		}
	}
}



#endif;
