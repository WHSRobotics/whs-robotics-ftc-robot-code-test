#pragma config(Hubs,  S1, HTMotor,  HTServo,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     robotMotor,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C2_1,    robotServo,           tServoNone)
#pragma config(Servo,  srvo_S1_C2_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"

task main()
{
	while(true)
	{
		float servoVal1 = ((256/180) * atan(joystick.joy1_y1 / joystick.joy1_x1));								//
		float servoVal2 = ((256/180) * (180 - abs(atan(joystick.joy1_y1 / joystick.joy1_x1))));		//
		float servoVal3 = 256/2;																																	//
		getJoystickSettings(joystick);
		if(joystick.joy1_x1 != 0 && joystick.joy1_y1 > 0)
		{
			servo[robotServo] = servoVal3;
			if(joystick.joy1_y1 < 0)
			{
				motor[robotMotor] = -100;
			}
			motor[robotMotor] = 100;
		}
		if(joystick.joy1_x1 < 0 && joystick.joy1_y1 > 0)
		{
			servo[robotServo] = servoVal2;
			if(joystick.joy1_y1 < 0)
			{
				motor[robotMotor] = -100;
			}
			motor[robotMotor] = 100;
		}
		if(joystick.joy1_x1 > 0 && joystick.joy1_y1 > 0)
		{
			servo[robotServo] = servoVal1;
			if(joystick.joy1_y1 < 0)
			{
				motor[robotMotor] = -100;
			}
			motor[robotMotor] = 100;
		}
		else
		{
			motor[robotMotor] = 0;
		}
	}
}
