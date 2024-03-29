#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     touchSensor,    sensorTouch)
#pragma config(Sensor, S3,     IRSensor,       sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S4,     gyroSensor,     sensorI2CHiTechnicGyro)
#pragma config(Motor,  motorA,          leftIntake,    tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          rightIntake,   tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     leftDrive,     tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     rightDrive,    tmotorTetrix, PIDControl, encoder)
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

task main()
{
		nMotorEncoder[leftDrive] = 0;                // reset the Motor Encoder of Motor B
		nMotorEncoder[rightDrive] = 0;                // reset the Motor Encoder of Motor C
		nMotorEncoderTarget[leftDrive] = 360;        // set the  target for Motor Encoder of Motor B to 360
		nMotorEncoderTarget[rightDrive] = 360;        // set the  target for Motor Encoder of Motor C to 360
		motor[leftDrive] = 75;                       // motor B is run at a power level of 75
		motor[rightDrive] = 75;                       // motor C is run at a power level of 75

		while(nMotorRunState[leftDrive] != runStateIdle && nMotorRunState[rightDrive] != runStateIdle)
		// while Motor B AND Motor C are still running (haven't yet reached their target):
		{
		  // do not continue
		}
		motor[leftDrive] = 0;                       // motor B is stopped at a power level of 0
		motor[rightDrive] = 0;                       // motor C is stopped at a power level of 0
}
