#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  motorA,          leftIntake,    tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          rightIntake,   tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     leftDrive,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     rightDrive,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     hangMotor,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     tableMotor,    tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C3_1,    armServo,             tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C3_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"

task DriveTrain()
{
	while(true)
	{
		getJoystickSettings(joystick);
		if(abs(joystick.joy1_y1) > 10)
		{
			motor[leftDrive] = 100;
		}
		if(abs(joystick.joy1_y2) > 10)
		{
			motor[rightDrive] = 100;
		}
		else
		{
			motor[leftDrive] = 0;
			motor[rightDrive] = 0;
		}
	}
}

task Intake()
{
	while(true)
	{
		getJoystickSettings(joystick);
		if(joy1Btn(6))
		{
			motor[leftIntake] = 100;
			motor[rightIntake] = 100;
		}
		if(joy1Btn(8))
		{
			motor[leftIntake] = -100;
			motor[rightIntake] = -100;
		}
		else
		{
			motor[leftIntake] = 0;
			motor[rightIntake] = 0;
		}
	}
}

task hangYourself()
{
	while(true)
	{
		getJoystickSettings(joystick);
		if(joy1Btn(1))
		{
			motor[hangMotor] = 100;
		}
		if(joy1Btn(3))
		{
			motor[hangMotor] = -100;
		}
		else
		{
			motor[hangMotor] = 0;
		}
	}
}

task turnTable()
{
	while(true)
	{
		getJoystickSettings(joystick);
		if(joy1_TopHat == 2)
		{
		motor[tableMotor] = 100;
		}
		if(joy1_TopHat == 4)
		{
			motor[tableMotor] = -100;
		}
		else
		{
			motor[tableMotor] = 0;
		}
	}
}

/*task dongers()
{
	while(true)
	{
		getJoystickSettings(joystick);
		if(joy1Btn(2))
		{
			servo[armServo] = 124 + 8;
		}
		if(joy1Btn(4))
		{
			servo[armServo] = 124 - 8;
		}
		else
		{
			servo[armServo] = 0;
		}
	}
}*/

task dongers()
{
	while(true)
	{
		getJoystickSettings(joystick);
		if(joy1Btn(2))
		{
			servo[armServo] = 124 + 8;
		}
		if(joy1Btn(4))
		{
			servo[armServo] = 124 - 8;
		}
	}
}

task main()
{
	while(true)
	{
		getJoystickSettings(joystick);
		StartTask(DriveTrain);
		StartTask(hangYourself);
		StartTask(turnTable);
		StartTask(Intake);
		StartTask(dongers);
	}
}
