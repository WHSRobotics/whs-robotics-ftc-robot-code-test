/*******************************************
** Header file for teleop functions (v.2) **
** for WHS Robotics FTC Team 542,         **
** for Ring It Up ('12-'13).              **
*******************************************/
//NEED TO DIVIDE BETWEEN CALCULATING AND ACTUAL DRIVING FUNCTIONS!!
//NEED MAJOR CLEANING UP BETWEEN FUNCTIONS AND TASKS
//USE SINE CHANGE RATE FOR SERVOS

#ifndef TELEOP_FUNCTIONS2;
#define TELEOP_FUNCTIONS2;


//-----------------------includes------------------------
#include "JoystickDriver.c";
#include "globalVars2.h";


//-----------------------functions-----------------------
//Float a value
int value_float(int currentPow, int reqPow, int increment)
{
  //initialize variables
  int changedPower = currentPow; //new power

  if(currentPow != reqPow) //does current power need to change?
  {
    if(currentPow > reqPow) //if current power greater than required power, lower current power
    {
      changedPower = currentPow - increment;
      if(changedPower < reqPow) //if changing power overshot required power
      {
        changedPower = reqPow; //set changed power to required power
      }
    }
    else //if current power less than required power, raise current power
    {
      changedPower = currentPow + increment;
      if(changedPower > reqPow) //if changing power overshot required power
      {
        changedPower = reqPow; //set changed power to required power
      }
    }
  }
  return changedPower;
}


//Move arm (up and down)
void arm_moveY()
{
  bool armCtrlActive = false;
  bool driveCtrlActive = false;

  if(abs(joystick.joy2_y2) > JOY_THRESHOLD)
  {
    armCtrlActive = true;
  }
  if((joy1Btn(6) == 1) || (joy1Btn(8) == 1))
  {
    driveCtrlActive = true;
  }

  if((armCtrlActive && !driveCtrlActive) || (armCtrlActive && driveCtrlActive))
  {
    //Arm controller gets priority
    motor[armLeft] = joystick.joy2_y2;
    motor[armRight] = joystick.joy2_y2;
  }
  else if(driveCtrlActive && !armCtrlActive)
  {
    //Drive controller gets priority
    if(joy1Btn(6) == 1 && joy1Btn(8) == 0) //L1 only; arm up
    {
      motor[armLeft] = MID_POW;
      motor[armRight] = MID_POW;
    }
    else if(joy1Btn(6) == 1 && joy1Btn(8) == 0) //L2 only; arm down
    {
      motor[armLeft] = -MID_POW;
      motor[armRight] = -MID_POW;
    }
  }
  else
  {
    //Both controllers inactive
    motor[armLeft] = STOP; //NEED FLOAT
    motor[armRight] = STOP;
  }
}


//Set arm heights
void arm_setHeight(int armHeight) //Need to check priority
{
  if(joy1Btn(5) == 0 || joy1Btn(6) == 0 || abs(joystick.joy2_y1) < JOY_THRESHOLD)
  {
	  motor[armLeft] = armHeight;
	  motor[armRight] = armHeight;
	  wait1Msec(1500); //magic #

	  motor[armLeft] = STOP; //NEED FLOAT
	  motor[armRight] = STOP;
	}
}




//D-pad relative turns

#endif
