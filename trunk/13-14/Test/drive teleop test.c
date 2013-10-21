#pragma config(Hubs,  S1, HTMotor,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     excel,          sensorI2CCustom)
#pragma config(Motor,  mtr_S1_C1_1,     leftDrive,     tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     rightDrive,    tmotorTetrix, openLoop)

#include "JoystickDriver.c";

task main()
{
	while(true)
	{
		getJoystickSettings(joystick);
		if(abs(joystick.joy1_y1) > 15 || abs(joystick.joy1_y2) > 15)
		{
			motor[leftDrive] = joystick.joy1_y1;
			motor[rightDrive] = joystick.joy1_y2;
		}
		else
		{
			motor[leftDrive] = 0;
			motor[rightDrive] = 0;
		}
	}
}
