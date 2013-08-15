/***************************************
** Header file for teleop tasks (v.1) **
** for WHS Robotics FTC Team 542,     **
** for Ring It Up ('12-'13).          **
***************************************/
#ifndef TELEOP_TASKS1;
#define TELEOP_TASKS1;

//-------------------includes------------------------
#include "teleop_functions1.h";


//-----------------------tasks-----------------------
task RunTankDrive()
{
  //initialize motor power variables
  int motorPower_left = 0;
  int motorPower_right = 0;

  while(true)
  {
    //update joystick
    getJoystickSettings(joystick);

    //set left drive train's power
	  if(abs(joystick.joy1_y1) > JOY_THRESHOLD)
	  {
	    //left driver joystick active: left motor set to left joystick value
	    motorPower_left = joystick.joy1_y1;
	  }
	  else
	  {
	    //left driver joystick not active: left motor does nothing
	    motorPower_left = STOP;
	  }
	  //set right drive train's power
	  if(abs(joystick.joy1_y2) > JOY_THRESHOLD)
	  {
	    //right driver joystick active: right motor set to right joystick value
	    motorPower_right = joystick.joy1_y2;
	  }
	  else
	  {
	    //right driver joystick not active: right motor does nothing
	    motorPower_right = STOP;
	  }

	  //move motors with assigned powers
    driveTrain_move(driveLeft_index, motorPower_left);
    driveTrain_move(driveRight_index, motorPower_right);
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


task RunClaw()
{
  bool reset_armCtrlActive = false;
  bool reset_driveCtrlActive = false;
  bool reset_armCtrlPriority = false;
  bool reset_driveCtrlPriority = false;

  while(true)
  {
    getJoystickSettings(joystick);
    claw_moveY();


    /*//check generic move or accurate move
	  bool moveY_isGeneric = false;
	  bool moveY_isAccurate = false;

	  if(abs(joystick.joy2_y2) > JOY_THRESHOLD)
	  {
	    moveY_isGeneric = true;
	  }
	  if(joy2Btn(5) == 1 || joy2Btn(7) == 1)
	  {
	    moveY_isAccurate = true;
	  }

	  //determine priorities
	  if(isGeneric && !isAccurate)
	  {
	    moveY_power = servo_joyToVal(joystick.joy2_y2);
	  }
	  else if((isAccurate && !isGeneric) || (isAccurate && isGeneric))
	  {
	    if(joy2Btn(5) == 1 && joy2Btn(7) == 0) //L1 only
	    {
	      if(moveY_power + ACC_INCREMENT < SERVO_MAX)
	      {
	        moveY_power = ServoValue[clawLeftY] + ACC_INCREMENT;
	      }
	      else
	      {
	        moveY_power = SERVO_MAX;
	      }
	    }
	    else if(joy2Btn(7) == 1 && joy2Btn(5) == 0) //L2 only
	    {
	      if(moveY_power - ACC_INCREMENT > SERVO_MIN)
	      {
	        moveY_power = ServoValue[clawLeftY] - ACC_INCREMENT;
	      }
	      else
	      {
	        moveY_power = SERVO_MIN;
	      }
	    }
	  }

	  servo[clawRightY] = moveY_power;
	  servo[clawLeftY] = moveY_power;*/




















    claw_moveX();


	  if(joy2Btn(3) == 1)
	  {
	    reset_armCtrlActive = true;
	  }
	  if(joy1Btn(3) == 1)
	  {
	    reset_driveCtrlActive = true;
	  }
	  if(reset_armCtrlActive || reset_driveCtrlActive)
	  {
	    claw_reset();
	  }
  }
  return;
}


#endif
