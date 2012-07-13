#include "JoystickDriver.c"
task main()
{
  while(true)  //loop forever
  {
    getJoystickSettings(joystick);  //access the current status of all parts of the joystick
    int motPower=0;  //set variables that will control the motor power
    int motPower2=0;

    if (joy1Btn(5) == 1)
      /*if button 5 on the joystick (top, upper left) is pressed, set the motor power variables to 100%*/
    {
      motPower=joystick.joy1_y1;
      motPower2=joystick.joy1_y2;
    }
    else
      /*if button 5 is not pressed, set the motor power variables at 1/3 */
    {
      motPower=joystick.joy1_y1/3;
      motPower2=joystick.joy1_y2/3;
    }
    motor[motorA]=motPower;  //run the motors at the power set by the variables
    motor[motorC]=motPower2;
    if (joy1Btn(6)==1)
    {
      motor[motorB]=100;
    }
    else
    {
      motor[motorB]=0;
    }
    /*if the button 6 (top upper right) is pressed, run the attachment motor up*/
    if(joy1Btn(8)==1)
    {
      motor[motorB]=-100;
    }
    else
    {
      motor[motorB]=0;
    }
    /*if button 8 is pressed (top lower right) is pressed, run the attachment motor down*/
  }
}
