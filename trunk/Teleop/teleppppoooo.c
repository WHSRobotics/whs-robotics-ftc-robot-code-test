#include "JoystickDriver.c"

void moveArmUp()
{
	motor[armRight] = 75;
	motor[armLeft] = 75;
}

void moveArmDown()
{
	motor[armRight] = -25;
	motor[armLeft] = -25;
}

void stopArm()
{
	motor[armRight] = 0;
	motor[armLeft] = 0;
}

void raiseFlags(float power)
{
	motor[motorB] = power;
	motor[motorC] = power;
}

task Arm()
{
 while(true)
   {
     getJoystickSettings(joystick);

    if (joy1Btn(6) == 1 && joy1Btn(8) == 0)
    {
   		moveArmDown();
   	}
   	else if (joy1Btn(8) == 1 && joy1Btn(6) == 0)
    {
   		moveArmUp();
   	}
   	else
   	{
   		stopArm();
   	}
}

task weightedRing()
{
	int eger = 0;
	while (true)
  {
  	eger = HTSMUXreadAnalogue(LEGOTOUCH);
    // Check if the sensor is pressed or not.
		if (eger == -1 || eger > 500) //not pressed
		{

		}
    else //pressed (>=500)
    {
    	raiseFlags(50);
			wait10Msec(50);
			raiseFlags(-50);
			wait10Msec(50);
    }
    wait1Msec(5);
	}
}

}
