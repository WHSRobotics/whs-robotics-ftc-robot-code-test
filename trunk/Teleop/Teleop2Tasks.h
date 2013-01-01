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
#include "common.h"
#include "hitechnic-sensormux.h"
#include "hitechnic-touchmux.h"
//const tMUXSensor TOUCH_SENSOR = msensor_S2_4;


///////////////////////GLOBAL VARIABLES////////////////////////
const int FLAG_POW = 50; //default power for flag movement
const int FLAG_RESET_TIME = 50; //flag reset time: .5 sec (50 10 Msec)
const int FLAG_REG_TIME = 12;
const int FLAG_ENCODERVAL = 45; //encoder value for flag to raise
const int ARM_UP_POW = 75;
const int ARM_DOWN_POW = -15;
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


void stopFlags()
{
  motor[flagLeft] = STOP;
  motor[flagRight] = STOP;
}


void resetFlags()
{
  motor[flagLeft] = -FLAG_POW;
  motor[flagRight] = -FLAG_POW;
  wait10Msec(FLAG_RESET_TIME);
  motor[flagLeft] = STOP;
  motor[flagRight] = STOP;

  nMotorEncoder[flagLeft] = 0;
	nMotorEncoder[flagRight] = 0;
	ClearTimer(T1);
}


void raiseFlags()
{
  motor[flagLeft] = FLAG_POW;
  motor[flagRight] = FLAG_POW;

  wait10Msec(FLAG_REG_TIME);

	stopFlags();
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


task Flags()
{
  ClearTimer(T1);
  bool hasMoved = false;

  while(true)
  {
    //TSval = HTSMUXreadAnalogue(TOUCH_SENSOR); //read touch sensor value

    //check status of touch sensor and if flag needs to reset
    bool isPressed = HTTMUXisActive(TUX, 2);

    // Check if the sensor is pressed or not.

    if(isPressed && !hasMoved) //pressed, flags have not yet moved
    {
      raiseFlags();
      hasMoved = true;
      PlayTone(400,5);
    }
    else if(!isPressed && hasMoved) //not pressed, flags moved
		{
      resetFlags();
      hasMoved = false;
      PlayTone(200, 5);
		}
    wait1Msec(5);
  }
}



#endif
