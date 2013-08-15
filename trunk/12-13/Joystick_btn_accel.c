/**************************************************
* This program is a tele-op program used to drive *
* an NXT robot.                                   *
* Btn2 = half pow, Btn3 = 75% pow,                *
* Btn4 = gradual pow, Btn6 = full pow.            *
* Use joystick1 (left) for controlling direction. *
***************************************************/
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- Includes and Initialization -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- //
//B is right motor, C is left motor

#include "JoystickDriver.c";

//initialize global variables for powers and joystick coordinates
float power = 0;
float halfPower = 0;
float gentleHighPower = 0;
float gentleLowPower = 0;
float joyY = 0;
float joyX = 0;
const int JOY_MAX = 128;


// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- Functions -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- //

/*****************************************
*** setPower is used to set            ***
*** the power of the motors based      ***
*** on the button pressed.             ***
**-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=**
*** Btn2 = half pow, Btn6 = full pow,  ***
*** Btn3 = 75% pow, Btn4 = gradual pow ***
******************************************/
void setPower()
{
    if(joy1Btn(2) == 1) //Button 2 for half power
    {
      power = 50;
    }
    else if(joy1Btn(6) == 1) //Button 6 for full power
    {
      power = 100;
    }
    else if(joy1Btn(3) == 1) //Button 3 for 75% power
    {
      power = 75;
    }
    else if(joy1Btn(4) == 1) //Button 4 for gradual power (increases with time when pressed)
    {
      if(power == 0)
      {
        power = 10;
      }
    }
    else
    {
      power = 0;
    }

    halfPower = power/2;
}



/********************************************
*** brake is used to cause the robot      ***
*** to brake by setting both motors to 0. ***
*********************************************/
void brake()
{
  motor[motorB] = 0;
  motor[motorC] = 0;
}



/*********************************************
*** moveStraight is used to make the       ***
*** robot move straight either backwards   ***
*** or forwards at a certain power level.  ***
**=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-**
** Parameters: motPow - amt of power       ***
**             isForward - move forward?   ***
**********************************************/
void moveStraight(int motPow, bool isForward)
{
  if(isForward) //move forward with given power level
  {
    motor[motorB] = motPow;
    motor[motorC] = motPow;
  }
  else //move backward with given power level
  {
    motor[motorB] = motPow*-1;
    motor[motorC] = motPow*-1;
  }
}



/*****************************************
*** moveHorizZone moves the robot      ***
*** either sharp left or right         ***
*** depending on joystick orientation. ***
******************************************/
void moveHorizZone()
{
  if(joyX > 0) //x is positive
  {
    //turn sharp right
    motor[motorC] = power;
    motor[motorB] = 0;
  }
  else //x is negative
  {
    //turn sharp left
    motor[motorC] = 0;
    motor[motorB] = power;
  }
}



/*****************************************
*** moveVertZone moves the robot       ***
*** either forward or backward         ***
*** depending on joystick orientation. ***
******************************************/
void moveVertZone()
{
  if(abs(joyX) < 40 && abs(joyY) > 40)//when in vert zone
  {
    if(joyY > 0) //y is positive
    {
      //move straight forward
      moveStraight(power, true);
    }
    else //y is negative
    {
      //move straight backward
      moveStraight(power, false);
    }
  }
}



/***************************************
*** getQuadrant returns the quadrant ***
*** the current joystick coordinate  ***
*** is in (1, 2, 3, 4)               ***
****************************************/
int getQuadrant()
{
  if(joyX > 0 && joyY > 0) //(+,+)
  {
    return 1;
  }
  else if(joyX < 0 && joyY > 0) //(-,+)
  {
    return 2;
  }
  else if(joyX < 0 && joyY < 0) //(-,-)
  {
    return 3;
  }
  else //(+,-)
  {
    return 4;
  }
}



/*******************************************
*** setGentlePowers is used to set       ***
*** the gentle powers for diagonal turns ***
*** based on joystick coordinates.       ***
********************************************/
void setGentlePowers()
{
  float turnAmt = 0;
  //Gentle powers are [half power] + or - [half power * amt of turn]
  if(joyX >= joyY) //gentler diagonal turn
  {
    turnAmt = abs(joyY)/JOY_MAX;
    gentleLowPower = halfPower - (halfPower*turnAmt);
    gentleHighPower = halfPower + (halfPower*turnAmt);
  }
  else //sharper diagonal turn
  {
    turnAmt = abs(joyX)/JOY_MAX;
    gentleLowPower = halfPower - (halfPower*turnAmt);
    gentleHighPower = halfPower + (halfPower*turnAmt);
  }
}



/******************************************
*** gentleTurn is used to make turns    ***
*** between the vertical and horizontal ***
*** zones (diagonal turns).             ***
**-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-**
** Parameters: quadrant - quadrant of    **
**                        joystick       **
**                        direction      **
*******************************************/
void gentleTurn(int quadrant)
{
  if(quadrant == 3 || quadrant == 4) //if negative quadrants
  {
    //make powers negative
    gentleLowPower = gentleLowPower*-1;
    gentleHighPower = gentleHighPower*-1;
  }
  if(quadrant == 1 || quadrant == 4) //if right quadrants
  {
    //turn right
    motor[motorB] = gentleLowPower;
    motor[motorC] = gentleHighPower;
  }
  else //if left quadrants
  {
    //turn left
    motor[motorB] = gentleHighPower;
    motor[motorC] = gentleLowPower;
  }
}




void contRotate(bool isRight, int til)
{
  int compass = SensorValue[S2];
  while(compass != til)
  {
    if(isRight)
    {
      motor[motorB] = 0;
      motor[motorC] = 50;
    }
    else
    {
      motor[motorB] = 50;
      motor[motorC] = 0;
    }
    compass = SensorValue[S2];
  }
}


/***************************************
***
****************************************/
void resetDirection()
{
  int dpad = joystick.joy1_TopHat;
  int compass = SensorValue[S2];
  if(dpad == 0) //forward
  {
    for(int count = 0; count < 5; count++)
    {
	    if(compass > 180)
	    {
	      contRotate(false, 180);
	    }
	    else
	    {
	      contRotate(true, 180);
	    }
    }
  }
  else if(dpad == 2) //right
  {
    for(int count = 0; count < 5; count++)
    {
	    if(compass > 270)
	    {
	      contRotate(false, 270);
	    }
	    else
	    {
	      contRotate(true, 270);
	    }
    }
  }
  else if(dpad == 4) //backward
  {
    for(int count = 0; count < 5; count++)
    {
	    if(compass > 180)
	    {
	      contRotate(true, 0);
	    }
	    else
	    {
	      contRotate(false, 0);
	    }
    }
  }
  else if(dpad == 6) //left
  {
    for(int count = 0; count < 5; count++)
    {
	    if(compass > 270 || compass < 90)
	    {
	      contRotate(true, 90);
	    }
	    else if(compass < 270)
	    {
	      contRotate(false, 90);
	    }
	  }
  }
}



/*****************************
*** Main function.         ***
******************************/
task main()
{
  while(true) //infinite loop
  {
    getJoystickSettings(joystick); //update joystick
    joyX = joystick.joy1_x1; //get x of left joystick
    joyY = joystick.joy1_y1; //get y of left joystick

    setPower(); //set power level based on buttons pressed

    if(joy1Btn(4) == 1 && power < 100) //gradually increment power if Btn4 pressed
    {
      power = power + 5;
      wait1Msec(100);
    }

    //determine direction of movement:
    if(abs(joyX) < 40 && abs(joyY) > 40)//when in vert zone
    {
      moveVertZone();
    }
    else if(abs(joyY) < 40 && abs(joyX) > 40)//when in horiz zone
    {
      moveHorizZone();
    }
    else
    {
      if(abs(joyY) > 20 && abs(joyX) > 20) //when turning diagonally (gentle turn)
      {
        setGentlePowers();
        gentleTurn(getQuadrant());
      }
      else //in dead zone
      {
        brake();
      }
    }

    if(joystick.joy1_TopHat != -1)
    {
      resetDirection();
    }
  }
}
