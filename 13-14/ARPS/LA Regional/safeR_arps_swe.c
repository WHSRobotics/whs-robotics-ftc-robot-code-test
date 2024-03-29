#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S3, HTServo,  HTServo,  none,     none)
#pragma config(Sensor, S2,     gyroSensor,     sensorI2CHiTechnicGyro)
#pragma config(Motor,  motorA,          hangmanMot,    tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          intakeL,       tmotorNXT, PIDControl, reversed, encoder)
#pragma config(Motor,  motorC,          intakeR,       tmotorNXT, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     sweBL,         tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     armL,          tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     sweFL,         tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     flagMot,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     sweBR,         tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     armR,          tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     sweFR,         tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C4_2,     winchMot,      tmotorTetrix, openLoop, reversed)
#pragma config(Servo,  srvo_S3_C1_1,    swiFR,                tServoStandard)
#pragma config(Servo,  srvo_S3_C1_2,    swiBR,                tServoStandard)
#pragma config(Servo,  srvo_S3_C1_3,    dropbox,              tServoStandard)
#pragma config(Servo,  srvo_S3_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S3_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S3_C1_6,    servo6,               tServoNone)
#pragma config(Servo,  srvo_S3_C2_1,    swiFL,                tServoStandard)
#pragma config(Servo,  srvo_S3_C2_2,    swiBL,                tServoStandard)
#pragma config(Servo,  srvo_S3_C2_3,    antiRatchet,          tServoStandard)
#pragma config(Servo,  srvo_S3_C2_4,    servo10,              tServoNone)
#pragma config(Servo,  srvo_S3_C2_5,    servo11,              tServoNone)
#pragma config(Servo,  srvo_S3_C2_6,    servo12,              tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/**********************************
** WHS Robotics  |  FTC Team 542 **
** Block Party! 2013-2014 Season **
** Dump (1st box)                **
** Main  |  Right  |  V1         **
***********************************/

#include "arps_functions_swedr.h"
#include "auto_globVars_swedr.h"
/////////DUMP AUTONOMOUS/////////

task RatchetHang()
{
	while(true)
	{
		servo[antiRatchet] = AR_CLOSED;
		//motor[hangmanMot] = -10;
	}
}

void drive(float distanceInches, float power)
{
		int targetDistance = distanceInches * INCH_ENCODERVALUE;// * abs(power)/power;

	nMotorEncoder[sweFL] = 0;
	//nMotorEncoder[sweFR] = 0;

	/*simpleMotor(sweFL, swiFL, power, dirAngle, 0, FL_SERVO_MAP);
	simpleMotor(sweBL, swiBL, power, dirAngle, -34, BL_SERVO_MAP);
	simpleMotor(sweFR, swiFR, power, dirAngle, -30, FR_SERVO_MAP);
	simpleMotor(sweBR, swiBR, power, dirAngle, -30, BR_SERVO_MAP);*/
	runDriveTrain(-power);

	while(abs(nMotorEncoder[sweFL]) <= targetDistance)/* || (nMotorEncoder[sweFL] <= targetDistance)*/
	{
		writeDebugStreamLine("FR: %f, FL: %f", nMotorEncoder[sweFR], nMotorEncoder[sweFL]);
	}

	stopDriveTrain();
}

//---------Function for initialization
void initializeRobot()
{
	servo[swiFL] = 127;
	servo[swiBL] = 127;
	servo[swiFR] = 127;
	servo[swiBR] = 127;
	StartTask(RatchetHang);

	wait1Msec(1000);

	muxUpdateInterval = 1;
	servoChangeRate[swiFL] = 0;
	servoChangeRate[swiFR] = 0;
	servoChangeRate[swiBR] = 0;
	servoChangeRate[swiBL] = 0;
	StartTask(HoldBox);

	return;
}

//MAIN//
task main()
{
	initializeRobot();
	waitForStart();
	//StartTask(hangArmMaintain);
	//--Lift arm concurrently
	StartTask(ScoreArm);
	//--Move towards crate
	moveStraight(117.0,18.0,100.0);
	//--Score box
	boxOpen = true;
	StopTask(HoldBox);
	dropTheBlock();
	//--Move away from crate
	moveStraight(80.0, 11.0,-100.0);
	//--Go onto ramp
	moveStraight(45.0,55.0,100.0);

	while(true){};
}
