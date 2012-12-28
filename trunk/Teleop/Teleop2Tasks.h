#ifndef TELEOP2TASKS;
#define TELEOP2TASKS;
/**********************************
** WHS Robotics  |  FTC Team 542 **
** Ring It Up! 2012-2013 Season  **
** Tele-Op Program 2.0           **
** Tasks                         **
***********************************/

///////////////////////////INCLUDES////////////////////////////
#include "JoystickDriver.c"



///////////////////////GLOBAL VARIABLES////////////////////////
const int ARM_UP_POW = 75;
const int ARM_DOWN_POW = -25;
const int STOP = 0;



/////////////////////////FUNCTIONS/////////////////////////////
void moveArmUp()
{
	motor[armRight] = ARM_UP_POW;
	motor[armLeft] = ARM_UP_POW;
}

void moveArmDown()
{
	motor[armRight] = ARM_DOWN_POW;
	motor[armLeft] = ARM_DOWN_POW;
}

void stopArm()
{
	motor[armRight] = STOP;
	motor[armLeft] = STOP;
}



/////////////////////////////TASKS/////////////////////////////
task Arm()
{
 while(true)
 {
	  getJoystickSettings(joystick); //update joystick readings

		if (joy1Btn(6) == 1 && joy1Btn(8) == 0) //R1 pressed and R2 not
		{
			moveArmDown();
		}
	 	else if (joy1Btn(8) == 1 && joy1Btn(6) == 0) //R2 pressed and R1 not
	  {
	 		moveArmUp();
	 	}
	 	else //nothing pressed or (R1 AND R2 pressed)
	 	{
	 		stopArm();
	 	}
	}
}



#endif
