#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  motorA,          leftIntake,    tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          rightIntake,   tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     leftDrive,     tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     rightDrive,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     leftArm,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     rightArm,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     hang1,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     hang2,         tmotorTetrix, openLoop, reversed)
#pragma config(Servo,  srvo_S1_C4_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_4,    intakeServo,          tServoStandard)
#pragma config(Servo,  srvo_S1_C4_5,    hangServo1,           tServoStandard)
#pragma config(Servo,  srvo_S1_C4_6,    hangServo2,           tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"
#include "teleop_globVars1.h"

void runIntake(int power)
{
	motor[leftIntake] = power;
	motor[rightIntake] = power;
}

void runArm(int power)
{
	motor[leftArm] = power;
	motor[rightArm] = power;
}

void joy2drive()
{
		//-----------joystick 2------------//
		//low priority
		//higher thresholds than joy1
		getJoystickSettings(joystick);
		motor[leftDrive] = abs(joystick.joy2_y1 * 25/32) > 25
		? joystick.joy2_y1 * 25/32 //if left movement is significant
		: 0; //if left movement is insignificant
		motor[rightDrive] = abs(joystick.joy2_y2 * 25/32) > 25
		? joystick.joy2_y2 * 25/32 //if right movement is significant
		: 0; //if right movement is insignificant
}

task DriveTrain()
{
	while(true)
	{
		//high priority
		//-----------joystick 1------------//
		getJoystickSettings(joystick);
		if(abs(joystick.joy1_y1 * 25/32) > 15 || abs(joystick.joy1_y2 * 25/32) > 15)//if movement is significant
		{
			motor[leftDrive] = joystick.joy1_y1 * 25/32;
			motor[rightDrive] = joystick.joy1_y2 *25/32;
		}
		else //if movement is insignificant
		{
			joy2drive();
		}
	}
}

void joy1Arm()
{
	while(true)
	{
		//-----------joystick 1------------//
		//low priority
		getJoystickSettings(joystick);
		if(joy1Btn(6) && !joy1Btn(8)) //move arm up
		{
			runArm(80);
		}
		else if(joy1Btn(8) && !joy1Btn(6)) //move arm down
		{
			runArm(-40);
		}
		else //if not pressed/pressed at same time
		{
			runArm(STOP);
		}
	}
}

task ScoringArm()
{
	while(true)
	{
		//-----------joystick 2------------//
		//high priority
		getJoystickSettings(joystick);
		if(joy2Btn(6) && !joy2Btn(8)) //move arm up
		{
			runArm(80);
		}
		else if(joy2Btn(8) && !joy2Btn(6)) //move arm down
		{
			runArm(-40);
		}
		else //if not pressed/pressed at same time
		{
			joy1Arm();
		}
	}
}

task Hang()
{
	while(true)
	{
		getJoystickSettings(joystick);
		//Activates winch lift motors
		motor[hang1] = joystick.joy1_TopHat == 0 && joystick.joy2_TopHat == 0
		?100
		:0;
		motor[hang2] = joystick.joy1_TopHat == 0 && joystick.joy2_TopHat == 0
		?100
		:0;
		//Only when the button for the lift arms are pressed, lift
		if(joy1Btn(1) && joy2Btn(1))
		{
			servoTarget[hangServo1] = 250;
			servoTarget[hangServo2] = 0;
		}
		//Otherwise, Drop the servo arms
		else
		{
			servoTarget[hangServo1] = 90;
			servoTarget[hangServo2] = 160;
		}
	}
}

task Intake()
{
	while(true)
	{
		getJoystickSettings(joystick);
		//Condition activates servo drop
		if(joy1Btn(5) || joy2Btn(5))
		{
			servoTarget[intakeServo] = 228;
			motor[rightIntake] = 0;
			motor[leftIntake] = 0;
		}
		//Re-enables and returns servo to initial position
		else
		{
			servoTarget[intakeServo] = 75;
			motor[leftIntake] = 100;
			motor[rightIntake] = 100;
		}
	}
}
