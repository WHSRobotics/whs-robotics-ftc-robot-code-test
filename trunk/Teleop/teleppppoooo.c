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

}
