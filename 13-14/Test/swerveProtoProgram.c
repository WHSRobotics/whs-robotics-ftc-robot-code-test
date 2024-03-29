
#pragma config(Hubs,  S1, HTServo,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Servo,  srvo_S1_C1_1,    robotServo,           tServoNone)
#pragma config(Servo,  srvo_S1_C1_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"

task main()
{
	while(true)
	{																																	//
		getJoystickSettings(joystick);
		float servoVal1 = ((256/180) * atan(joystick.joy1_y1 / joystick.joy1_x1));								//
		float servoVal2 = ((256/180) * (180 - abs(atan(joystick.joy1_y1 / joystick.joy1_x1))));		//
		float servoVal3 = 256.0/2.0;
		if(joystick.joy1_x1 == 0)
		{
			servo[robotServo] = servoVal3;
		}
		else if(joystick.joy1_x1 < 0)
		{
			servo[robotServo] = servoVal2;
		}
		else if(joystick.joy1_x1 > 0)
		{
			servo[robotServo] = servoVal1;
		}
		if(joystick.joy1_y1 < -15)
		{
			motor[motorA] = -100;
			//motor[robotMotor] = -100;
		}
		else if(joystick.joy1_y1 > 15)
		{
			motor[motorA] = 100;
		}
		//motor[robotMotor] = 100;
		else
		{
			motor[motorA] = 0;
			//motor[robotMotor] = 0;
		}
	}
}
