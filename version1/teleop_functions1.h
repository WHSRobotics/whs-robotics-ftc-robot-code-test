/*******************************************
** Header file for teleop functions (v.1) **
** for WHS Robotics FTC Team 542,         **
** for Ring It Up ('12-'13).              **
*******************************************/
//NEED TO DIVIDE BETWEEN CALCULATING AND ACTUAL DRIVING FUNCTIONS!!
//NEED MAJOR CLEANING UP BETWEEN FUNCTIONS AND TASKS
//USE SINE CHANGE RATE FOR SERVOS

#ifndef TELEOP_FUNCTIONS1;
#define TELEOP_FUNCTIONS1;


//-----------------------includes------------------------
#include "JoystickDriver.c";
#include "globalVars1.h";


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


//Scale servo value to joystick
int servo_joyToVal(int joyVal)
{
  getJoystickSettings(joystick); //update joystick

  //find the proportional servo position using the equation of a line
  float eqSlope = (SERVO_MAX_FP - SERVO_MIN_FP)/(JOY_MAX_FP - JOY_MIN_FP); //slope of line, using max and min of servo and joystick
  float scaledJoy = -eqSlope * joyVal; //-mx of line for correct direction control of servo
  float yInt = -eqSlope * JOY_MAX_FP + SERVO_MAX_FP; //y-intercept of line
  int servoPos = scaledJoy + yInt; //equation of line

  return servoPos; //return calculated servo position (in int)
}


//Float value specifically for resetting claw
//Parameters: clawLeftX_index = 0
//            clawRightX_index = 1
//            clawLeftY_index = 2
//            clawRightY_index = 3
void claw_reset_float(int servoName)
{
  if(servoName == 0)
  {
    servo[clawLeftX] = value_float(ServoValue[clawLeftX], SERVO_STANDARD, QUICK_INCREMENT);
  }
  else if(servoName == 1)
  {
    servo[clawRightX] = value_float(ServoValue[clawRightX], SERVO_STANDARD, QUICK_INCREMENT);
  }
  else if(servoName == 2)
  {
    servo[clawLeftY] = value_float(ServoValue[clawLeftY], SERVO_STANDARD, QUICK_INCREMENT);
  }
  else if(servoName == 3)
  {
    servo[clawRightY] = value_float(ServoValue[clawRightY], SERVO_STANDARD, QUICK_INCREMENT);
  }
}


//Calculate new value for claw's X's left servo based on action
int claw_calcLeftVal(int currLeftVal, string action)
{
  int newLeftVal = currLeftVal;
  int currRightVal = SERVO_MAX - currLeftVal;

  if(strcmp(action, "close") == 0)
  {
    //if doesn't overshoot fully closed, close claw regularly by increment
    if((currLeftVal + ACC_INCREMENT < SERVO_MAX) || (currRightVal - ACC_INCREMENT < SERVO_MIN))
    {
      newLeftVal += ACC_INCREMENT;
    }
    //if overshoots fully closed, set to fully closed
    else
    {
      newLeftVal = SERVO_MAX;
    }
  }
  else if(strcmp(action, "open") == 0) //Open; need to check!
  {
    //if doesn't overshoot fully open, open claw regularly by increment
    if((currLeftVal - ACC_INCREMENT > SERVO_MIN) || (currRightVal + ACC_INCREMENT < SERVO_MAX))
    {
      newLeftVal -= ACC_INCREMENT;
    }
    //if overshoots fully open, set to fully open
    else
    {
      newLeftVal = SERVO_MIN;
    }
  }

  return newLeftVal;
}


//Move drive train
//Parameters: driveLeft_index = 0
//            driveRight_index = 1
void driveTrain_move(int motorName, int motorPower)
{
  //apply motor power to corresponding motor
  if(motorName == 0)
  {
    motor[driveLeft] = motorPower;
  }
  else if(motorName == 1)
  {
    motor[driveRight] = motorPower;
  }
}


//Move arm (up and down) **MORE MOTORS?!
void arm_moveY()
{
  bool armCtrlActive = false;
  bool driveCtrlActive = false;

  if(abs(joystick.joy2_y2) > JOY_THRESHOLD)
  {
    armCtrlActive = true;
  }
  if((joy1Btn(5) == 1) || (joy1Btn(7) == 1))
  {
    driveCtrlActive = true;
  }

  if((armCtrlActive && !driveCtrlActive) || (armCtrlActive && driveCtrlActive)) //need to check active
  {
    //Arm controller gets priority
    motor[armLeft] = joystick.joy2_y2;
    motor[armRight] = joystick.joy2_y2;
  }
  else if(driveCtrlActive && !armCtrlActive)
  {
    //Drive controller gets priority
    if(joy1Btn(5) == 1 && joy1Btn(7) == 0) //L1 only; arm up
    {
      motor[armLeft] = MID_POW;
      motor[armRight] = MID_POW;
    }
    else if(joy1Btn(7) == 1 && joy1Btn(5) == 0) //L2 only; arm down
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
    return; //this is supposed to break out of this function but iono if it works
  }
  motor[armLeft] = armHeight;
  motor[armRight] = armHeight;
  wait1Msec(1500); //magic #

  motor[armLeft] = STOP; //NEED FLOAT
  motor[armRight] = STOP;
}


//Move claw (up and down, generic and accurate)
void claw_moveY()
{
  //check generic move or accurate move
  bool moveY_isGeneric = false;
  bool moveY_isAccurate = false;
  int moveY_power = 0;

  if(abs(joystick.joy2_y2) > JOY_THRESHOLD)
  {
    moveY_isGeneric = true;
  }
  if(joy2Btn(5) == 1 || joy2Btn(7) == 1)
  {
    moveY_isAccurate = true;
  }

  //determine priorities
  if(moveY_isGeneric && !moveY_isAccurate)
  {
    moveY_power = servo_joyToVal(joystick.joy2_y2);
  }
  else if((moveY_isAccurate && !moveY_isGeneric) || (moveY_isAccurate && moveY_isGeneric))
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
  servo[clawLeftY] = moveY_power;
}


//Move claw (open and close)
void claw_moveX()
{
  bool armCtrlActive = false;
  bool driveCtrlActive = false;

  //check if arm controller active
  if(joy2Btn(6) == 1 || joy2Btn(8) == 1)
  {
    armCtrlActive = true;
  }
  //check if drive train controller active
  if(joy1Btn(6) == 1 || joy1Btn(8) == 1)
  {
    driveCtrlActive = true;
  }

  int currLeftVal = ServoValue[clawLeftX];
  int currRightVal = SERVO_MAX - currLeftVal;
  int newLeftVal = currLeftVal;
  int newRightVal = currRightVal;
  string action = "";

  if((armCtrlActive && !driveCtrlActive) || (armCtrlActive && driveCtrlActive))
  {

    if(joy2Btn(6) == 1 && joy2Btn(8) == 0) //Close; need to check!
    {
    	action = "close";
      newLeftVal = claw_calcLeftVal(currLeftVal, action);
    }
    else if(joy2Btn(8) == 1 && joy2Btn(6) == 0) //Open; need to check!
    {
    	action = "open";
      newLeftVal = claw_calcLeftVal(currLeftVal, action);
    }
  }
  else if(driveCtrlActive && !armCtrlActive)
  {
    if(joy1Btn(6) == 1 && joy1Btn(8) == 0) //Close; need to check!
    {
    	action = "close";
      newLeftVal = claw_calcLeftVal(currLeftVal, action);
    }
    else if(joy1Btn(8) == 1 && joy1Btn(6) == 0) //Open; need to check!
    {
    	action = "open";
      newLeftVal = claw_calcLeftVal(currLeftVal, action);
    }
  }
  newRightVal = SERVO_MAX - newLeftVal; //synchronize right value with left

  //set servo values
  servo[clawLeftX] = newLeftVal;
  servo[clawRightX] = newRightVal;
}


//Reset claw to standard position
void claw_reset()
{
  /*claw_reset_float(clawLeftX_index);
  claw_reset_float(clawRightX_index);
  claw_reset_float(clawLeftY_index);
  claw_reset_float(clawRightY_index);*/

  servo[clawLeftX] = 0;
  servo[clawRightX] = 0;
  servo[clawLeftY] = 0;
  servo[clawRightY] = 0;
  wait10Msec(500);



}


//D-pad relative turns

#endif
