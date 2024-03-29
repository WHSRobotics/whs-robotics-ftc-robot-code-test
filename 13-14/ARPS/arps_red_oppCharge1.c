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

/**********************************
** WHS Robotics  |  FTC Team 542 **
** Block Party! 2013-2014 Season **
** Opponent Charge (Ramp Only)   **
** Main  |  Red  |  V1           **
***********************************/

////////////////////////INCLUDES////////////////////
#include "JoystickDriver.c"; //driver for receiving bluetooth msgs
#include "arps_functions1.h"; //header file for ARP Functions


//INITIALIZATION//
void initializeRobot()
{
  resetHang(); //hang arm
  resetBucket(); //DO NOT reset the NXT motors!!

	//reset drive train encoders
	nMotorEncoder[leftDrive] = 0;
	nMotorEncoder[rightDrive] = 0;

	//beep to signal end of initialization
	PlayTone(440, 30);

  return;
}



////////////////MAIN////////////////

task main()
{
	initializeRobot();

	waitForStart();

	//----------OPP CHARGE BEGIN------------
	//---Move forward onto ramp.
	moveStraight(68.0, 100);

	//---Stop
	stopDriveTrain();
}
