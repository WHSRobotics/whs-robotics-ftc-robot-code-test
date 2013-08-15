/*******************************************
* This program is a tele-op program used   *
* to drive an NXT robot. Hold down Btn2    *
* for half power; Btn6 for full power.     *
* Use the D-Pad for controlling direction. *
********************************************/
//B is right motor, C is left motor

#include "JoystickDriver.c";

//initialize global variables for powers
int power = 0;
int gentleHighPower = 0;
int gentleLowPower = 0;

/****************************************
*** setPower is used to set           ***
*** the power of the motors based     ***
*** on the button pressed.            ***
*** Btn2 = half pow, Btn6 = full pow. ***
*****************************************/
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
    else
    {
      power = 0;
    }

    //Calculate powers for gentle turns
    gentleHighPower = power/2 + power/4;
    gentleLowPower = power/2 - power/4;
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
  else //more backward with given power level
  {
    motor[motorB] = motPow*-1;
    motor[motorC] = motPow*-1;
  }
}



/*********************************************
*** turn makes the robot turn (yes really) ***
*** based on if the turn is sharp/gentle,  ***
*** right/left, and forward/backward.      ***
**-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=**
** Parameters: isSharp - sharp turn or not? **
**             isRight - right turn or not? **
**             isForward - forward or not?  **
**********************************************/
void turn(bool isSharp, bool isRight, bool isForward)
{
  if(!isForward) //if turn backwards, make power levels negative
  {
    gentleHighPower = gentleHighPower*-1;
    gentleLowPower = gentleLowPower*-1;
  }
  if(isRight) //Right turns
  {
    if(isSharp) //sharp right turn
    {
      motor[motorC] = power;
		  motor[motorB] = 0;
		}
		else //gentle right turn
		{
		  motor[motorC] = gentleHighPower;
	    motor[motorB] = gentleLowPower;
    }
  }
  else //Left turns
  {
    if(isSharp) //sharp left turn
    {
      motor[motorC] = 0;
      motor[motorB] = power;
    }
    else //gentle left turn
    {
      motor[motorC] = gentleLowPower;
      motor[motorB] = gentleHighPower;
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
    int dpad = joystick.joy1_TopHat; //assign directional pad value to dpad
    bool sharpTurn; bool rightTurn; bool forwardMove; //declare vars used to determine turns

    setPower(); //set power level based on buttons pressed

    if(dpad != -1) //when a dpad button is pressed
    {
	    if(dpad == 0 || dpad == 4) //if top or bottom button, move straight
	    {
	      if(dpad == 0)
	      {
	        //move straight forward
	        forwardMove = true;
	        moveStraight(power, forwardMove);
	      }
	      else
	      {
	        //move straight backward
	        forwardMove = false;
	        moveStraight(power, forwardMove);
	      }
	    }
	    else
	    {
	      if(dpad == 1) //top right dpad button
	      {
	      //gentle right fow
	      sharpTurn = false;
	      rightTurn = true;
	      forwardMove = true;
	      }
		    else if(dpad == 2) //right dpad button
		    {
		      //sharp right
		      sharpTurn = true;
		      rightTurn = true;
		      forwardMove = true;
		    }
		    else if(dpad == 3) //bottom right dpad button
		    {
		      //gentle right back
		      sharpTurn = false;
		      rightTurn = true;
		      forwardMove = false;
		    }
		    else if(dpad  == 5) //bottom left dpad button
		    {
		      //gentle left back
		      sharpTurn = false;
		      rightTurn = false;
		      forwardMove = false;
		    }
		    else if(dpad == 6) //left dpad button
		    {
		      //sharp left
		      sharpTurn = true;
		      rightTurn = false;
		      forwardMove = true;
		    }
		    else if(dpad == 7) //top left dpad button
		    {
		      //gentle left fow.
		      sharpTurn = false;
		      rightTurn = false;
		      forwardMove = true;
		    }
		    turn(sharpTurn, rightTurn, forwardMove);
	    }
	  }
	  else //if dpad isn't pressed, then brake
	  {
	    brake();
	  }
  }
}
