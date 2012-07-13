#include "JoystickDriver.c"
task main()
{
  while(true)
  {
    getJoystickSettings(joystick);
    int motPower=0;
    int motPower2=0;

    if (joy1Btn(5) == 1)
    {
      motPower=joystick.joy1_y1;
      motPower2=joystick.joy1_y2;
    }
    else
    {
      motPower=joystick.joy1_y1/3;
      motPower2=joystick.joy1_y2/3;
    }
    motor[motorA]=motPower;
    motor[motorC]=motPower2;
    if (joy1Btn(6)==1)
    {
      motor[motorB]=100;
    }
    else
    {
      motor[motorB]=0;
    }
    if(joy1Btn(8)==1)
    {
      motor[motorB]=-100;
    }
    else
    {
      motor[motorB]=0;
    }
  }
}
