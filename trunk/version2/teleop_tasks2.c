/***************************************
** Header file for teleop tasks (v.2) **
** for WHS Robotics FTC Team 542,     **
** for Ring It Up ('12-'13).          **
***************************************/
#ifndef TELEOP_TASKS2;
#define TELEOP_TASKS2;

//-------------------includes------------------------
#include "teleop_functions2.h";


//-----------------------tasks-----------------------
task RunTankDrive()
{
  //initialize motor power variables
  int goalPow_left = 0;
  int goalPow_right = 0;
	int currPow_left = 0;
	int currPow_right = 0;

	float driveRate = 1.0;

  while(true)
  {
    //update joystick
    getJoystickSettings(joystick);

  	if(joy1Btn(5) == 1)
  	{
  		driveRate = 1.0/3.0;
 		}
  	else
  	{
   		driveRate = 1.0;
    }

    //set left drive train's power
	  if(abs(joystick.joy1_y1) > JOY_THRESHOLD)
	  {
	    //left driver joystick active: left motor set to left joystick value
	    goalPow_left = joystick.joy1_y1*driveRate;
	  }
	  else
	  {
	    //left driver joystick not active: left motor does nothing
	    goalPow_left = STOP;
	  }
	  //set right drive train's power
	  if(abs(joystick.joy1_y2) > JOY_THRESHOLD)
	  {
	    //right driver joystick active: right motor set to right joystick value
	    goalPow_right = joystick.joy1_y2*driveRate;
	  }
	  else
	  {
	    //right driver joystick not active: right motor does nothing
	    goalPow_right = STOP;
	  }

	  //float power level and move motors
		while(currPow_left < goalPow_left)
		{
			currPow_left = value_float(currPow_left, goalPow_left, QUICK_INCREMENT);
	  	motor[driveLeft] = currPow_left;
	  	wait1Msec(500);
	  }
	  while(currPow_right < goalPow_right)
	  {
	  	currPow_right = value_float(currPow_right, goalPow_right, QUICK_INCREMENT);
	  	motor[driveRight] = currPow_right;
	  	wait1Msec(500);
	  }
  }
  return;
}


task RunArm()
{
  while(true)
  {
    getJoystickSettings(joystick);
    arm_moveY();
    //arm_setHeight(int armHeight);
  }
  return;
}




#endif
