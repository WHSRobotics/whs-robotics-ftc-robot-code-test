#pragma config(Hubs, S1, HTMotor, HTMotor, HTMotor, HTServo)
#pragma config(Sensor, S1, , sensorI2CMuxController)
#pragma config(Sensor, S2, touchSensor, sensorTouch)
#pragma config(Sensor, S3, IRSensor, sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S4, gyroSensor, sensorI2CHiTechnicGyro)
#pragma config(Motor, motorA, rightIntake, tmotorNXT, PIDControl, encoder)
#pragma config(Motor, motorB, leftIntake, tmotorNXT, PIDControl, encoder)
#pragma config(Motor, motorC, , tmotorNXT, openLoop)
#pragma config(Motor, mtr_S1_C1_1, leftDrive, tmotorTetrix, PIDControl, reversed)
#pragma config(Motor, mtr_S1_C1_2, rightDrive, tmotorTetrix, PIDControl)
#pragma config(Motor, mtr_S1_C2_1, leftArm, tmotorTetrix, openLoop, reversed)
#pragma config(Motor, mtr_S1_C2_2, rightArm, tmotorTetrix, openLoop)
#pragma config(Motor, mtr_S1_C3_1, hang1, tmotorTetrix, openLoop)
#pragma config(Motor, mtr_S1_C3_2, hang2, tmotorTetrix, openLoop, reversed)
#pragma config(Servo, srvo_S1_C4_1, flagServo, tServoStandard)
#pragma config(Servo, srvo_S1_C4_2, servo2, tServoNone)
#pragma config(Servo, srvo_S1_C4_3, autoServo, tServoStandard)
#pragma config(Servo, srvo_S1_C4_4, intakeServo, tServoStandard)
#pragma config(Servo, srvo_S1_C4_5, hangServo1, tServoStandard)
#pragma config(Servo, srvo_S1_C4_6, hangServo2, tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard       !!*//

/**********************************
** WHS Robotics  |  FTC Team 542 **
** Block Party! 2013-2014 Season **
** Dump (1st box)                **
** Main  |  Right  |  V1         **
***********************************/

#include "arps_functions.h" //header file for ARP Functions

//INITIALIZATION//
//-----------Global Variables
bool needArm = false; //to trigger concurrent movement in the arm, while moving other parts

//-----------Task to keep servos locked
task LockServos()
{
	while(true)
	{
		resetHang();
		resetFlag();
	}
}

//------------Task to move the arm concurrently
task Arm()
{
	while(true)
	{
		if(needArm)
		{
			moveArm(80);
			wait1Msec(500);
			moveArm(0);
			return;
		}
	}
}

//---------Function for initialization
void initializeRobot()
{
	//ready KONSTANTS
	const int AUTO_INIT = 15;

	//set to ready positions
	servo[autoServo] = AUTO_INIT;

	resetBucket(); //DO NOT reset the NXT motors!!

	//reset drive train encoders
	nMotorEncoder[leftDrive] = 0;
	nMotorEncoder[rightDrive] = 0;

	//lock hang arms
	StartTask(LockServos);
	//start task to lift arm concurrently
	StartTask(Arm);

	//beep to signal end of significance
	PlayTone(440,30);

	return;
}


//MAIN//
task main()
{
	initializeRobot();
	waitForStart();
	//TIME TO BEGIN//
	//---Lift arm
	moveArm(80);
	wait10Msec(60);
	moveArm(0);
	//---Move forward
	moveStraight(13.0,50);
	//---Release the waffle!
	servo[intakeServo] = 150;
	wait1Msec(1000);
	servo[intakeServo] = 80;
	wait1Msec(5000);
}
