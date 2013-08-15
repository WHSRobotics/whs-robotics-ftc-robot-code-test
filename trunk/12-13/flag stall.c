#pragma config(Motor,  motorB,          flagLeft,      tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          flagRight,     tmotorNXT, PIDControl, encoder)

#include "JoystickDriver.c"

bool auto = true;

task main()
{
	motor[flagLeft] = -50;
	motor[flagRight] = -50;

	wait10Msec(50);

	motor[flagLeft] = 0;
	motor[flagRight] = 0;

  while(true)
  {
  	getJoystickSettings(joystick);
  	if(joy1Btn(4) == 1)
  	{
  		if(auto == false)
  		{
  			auto = true;
  		}
  		else
  		{
  			auto = false;
  		}
  	}

  	if(auto == false)
  	{
	  	if(abs(joystick.joy1_x1) > 30)
	  	{
	  		if(joystick.joy1_x1 > 0)
	  		{
	  			motor[flagLeft] = joystick.joy1_x1/2;
	  		}
	  		else
	  		{
	  			motor[flagLeft] = -joystick.joy1_x1/2;
	  		}
	  	}
	  	if(abs(joystick.joy1_x2) > 30)
	  	{
	  		if(joystick.joy1_x2 > 0)
	  		{
	  			motor[flagLeft] = joystick.joy1_x2/2;
	  		}
	  		else
	  		{
	  			motor[flagLeft] = -joystick.joy1_x2/2;
	  		}
	  	}
	  }
  	else
  	{
		  motor[flagLeft] = 25;
		  motor[flagRight] = 25;

		  wait10Msec(50);

		  motor[flagLeft] = -25;
		  motor[flagRight] = -25;

		  wait10Msec(50);
		}
	}
}
