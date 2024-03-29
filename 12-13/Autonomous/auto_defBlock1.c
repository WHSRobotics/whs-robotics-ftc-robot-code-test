#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S2,     IRSensor,       sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S3,     TUX,            sensorHiTechnicTouchMux)
#pragma config(Sensor, S4,     gyroRobot,      sensorI2CHiTechnicGyro)
#pragma config(Motor,  motorA,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorB,          flagLeft,      tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          flagRight,     tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     driveRight,    tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     driveLeft,     tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     armRight,      tmotorTetrix, PIDControl, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     armLeft,       tmotorTetrix, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/***********************************
** WHS Robotics  |  FTC Team 542  **
** Ring It Up! 2012-2013 Season   **
** Autonomous Series 2            **
** Defensive blocking							**
** Main  |  Blue or Red  |  V1    **
***********************************/


///////////////////////////INCLUDES////////////////////////////
#include "JoystickDriver.c"  //file to "handle" the Bluetooth messages.
#include "autonomous_constants_globVars.h"  //header file with autonomous KONSTANTS and global variables
#include "autonomous_functions1.h"  //header file with autonomous functions
#include "autonomous_tasks1.h"  //header file with autonomous tasks



////////////////////////INITIALIZATION/////////////////////////
void initializeRobot()
{
  resetArm();

	//reset drive train encoders
	nMotorEncoder[driveLeft] = 0;
	nMotorEncoder[driveRight] = 0;

	HTGYROstartCal(gyroRobot); //calibrate gyro

	//clear timers T1 and T2
	ClearTimer(T1);
	ClearTimer(T2);

	resetFlags();

	//beep (because it's Windsor)
	PlayTone(440, 30);

  return;
}


//---------------------TASKS---------------------------
task LiftArm()
{
	//Lift arm while moving
	moveArm(6, 1250);
}



//-----------------------MAIN---------------------------
task main()
{
	initializeRobot();

	waitForStart(); // Wait for the beginning of autonomous phase.

	StartTask(LiftArm);


	///MOVE TO OTHER SIDE
	moveStraight(60,100);

	///ALIGNING
	//Take an IR reading.
	//right >= 8
	//IRVal = HTIRS2readACDir(IRSensor);
	  IRVal = SensorValue[IRSensor];

	if(IRVal != 1)
	{
		//right is >= 8
		//Turn to block right peg
		gyroCenterPivot(52,100);
		moveStraight(5,100);
		//---------------------IR BEACON IS ON LEFT/MIDDLE----------------------
		if(IRVal < 8)
		{
			//Move forward to block middle peg
			moveStraight(30,100);
			//Take an IR reading
			//IRVal = HTIRS2readACDir(IRSensor);
			IRVal = SensorValue[IRSensor];
			//---------------------IR BEACON IS ON LEFT---------------------------
			if(IRVal <= 7)
			{
				//Move forward to block left peg
				moveStraight(13, 100);
			}
			else
			{
				moveStraight(10, -100);
			}
		}
	}
}
