#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  HTMotor)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  motorA,          leftIntake,    tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          rightIntake,   tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     leftDrive,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     rightDrive,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     hangMotor,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     tableMotor,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     leftArm,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     rightArm,      tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C3_1,    intakeServo,          tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "teleop_tasks1.h";
#include "teleop_globVars1.h";

task main()
{
	while(true)
	{
		getJoystickSettings(joystick);

		StartTask(Arm);
		StartTask(DriveTrain);
		StartTask(Hang);
		StartTask(Intake);
		StartTask(Turntable);

	}
}