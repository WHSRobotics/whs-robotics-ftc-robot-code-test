#ifndef ARPS_FUNCTIONS.H:
#define ARPS_FUNCTIONS.H;

/////////////////////////INCLUDES/////////////////////////////
#include "auto_globVars1.h" //Header file with constants and global variables

/**********************************
** WHS Robotics  |  FTC Team 542 **
** Block Party! 2013-2014 Season **
** Autonomous (ARPS) V1          **
** Functions                     **
***********************************/



//--------------MOVES AND STOPS-----------------
/**************************************
** stopDriveTrain sets both drive    **
** train motors to a specific power. **
***************************************/
void stopDriveTrain()
{
	motor[leftDrive] = STOP;
	motor[rightDrive] = STOP;
}

/**************************************
** moveStraight moves the robot      **
** forward a specified distance at   **
** a specified power using encoders  **
*--------------------------------------
* Parameters:
* float distanceInches - distance to move in inches
* int pwr - motor power for drive train
***************************************/
void moveStraight(float distanceInches, int pwr)
{
	float targetDistance = distanceInches*INCH_ENCODERVALUE; //convert in to encoder val
	float leftPwr = pwr;
	float rightPwr = pwr;

	//reset motor encoders
	nMotorEncoder[leftDrive] = 0;
	nMotorEncoder[rightDrive] = 0;

	//set encoder targets
	nMotorEncoderTarget[leftDrive] = targetDistance;
	nMotorEncoderTarget[rightDrive] = targetDistance;

	//start drive motors
	motor[leftDrive] = leftPwr;
	motor[rightDrive] = rightPwr;

	while(nMotorRunState[leftDrive] != runStateIdle && nMotorRunState[rightDrive] != runStateIdle)
	{} //do nothing while motors still running

	stopDriveTrain();
}


/**************************************
** moveArm sets both arm motors to   **
** a specific power.                 **
***************************************/
void moveArm(int power)
{
	motor[leftArm] = power;
	motor[rightArm] = power;
}


//-------------------------RESETS----------------------
/**************************************
** resetBucket closes the intake     **
** bucket to initial position.       **
***************************************/
void resetBucket()
{
	servo[intakeServo] = 80;
}


/**************************************
** resetHang drops the hang arms     **
** to initial position.              **
***************************************/
void resetHang()
{
	servo[hangServo1] = 60;
	servo[hangServo2] = 180;
}


/**************************************
** resetFlag sets the flag servo     **
** at initial position (ready)       **
***************************************/
void resetFlag()
{
	servo[flagServo] = 125;
}

void resetGlobVars()
{
	currentValue = 0.0;
	angleChange = 0.0;
	timeChange = 0.0;
	gCurrTotalMove = 0.0;
	sCurrTotalTurn = 0.0;
	remainingTurn = DEFAULT_VAL;
	error = 0.0;
	adjustedTarget = 0.0;
}

//---------------------------------GYRO-------------------------
/**************************************
** getAngleChange gives an updated   **
** change in angle.                  **
***************************************/
float getAngleChange()
{
	currentValue = HTGYROreadRot(gyroSensor); //gyroReading - BIAS
	timeChange = time1[T1]/MILLISECOND; //change in time (sec)

	ClearTimer(T1);

	angleChange = currentValue * timeChange;
	return angleChange;
}

/***************************************
** getCurrTotalMove gives a current   **
** running total of turn for the gyro **
****************************************/
float getCurrTotalMove(float currTotal)
{
	currTotal += getAngleChange();
	return currTotal;
}


/**************************************
** gyroCenterPivot turns the robot   **
** accurately using the gyro sensor. **
** Turns at a certain speed until it **
** gets to turnDirection.            **
*-------------------------------------
* Parameters:
* int turnDirection - Num degrees to turn
* int speedKonstant - Speed to turn at; power
***************************************/
void gyroCenterPivot(int turnDirection, int speedKonstant)
{
	//Initialization
	HTGYROstartCal(gyroSensor); //Calibrate gyro sensor
	ClearTimer(T1);

	adjustedTarget = ADJUST_M * turnDirection - ADJUST_B; //scale target angle linearly
	float turn = 100.0; //default pwr for drive train motors

	while(abs(remainingTurn) > TURN_THRESHOLD)
	{
		remainingTurn = adjustedTarget - gCurrTotalMove; //find # of degrees left to turn
		gCurrTotalMove += getAngleChange();
		error = adjustedTarget - gCurrTotalMove;
		turn = error * speedKonstant; //find pwr for DT motors

		//apply calculated turn pwr to DT motors
		motor[leftDrive] = turn;
		motor[rightDrive] = -turn;

		wait10Msec(1);
	}

	//done turning
	stopDriveTrain();
	resetGlobVars();
}


/**************************************
** gyroSidePivot turns the robot     **
** accurately, driving on one side   **
**  using the gyro sensor.           **
** Turns at a certain speed until it **
** gets to turnDirection.            **
*-------------------------------------
* Parameters:
* int turnDirection - Num degrees to turn (+right, -left)
* int speedKonstant - Speed to turn at; power (+forward, -backwards)
***************************************/
void gyroSidePivot(int turnDirection, int speedKonstant)
{
	//Initialization
	HTGYROstartCal(gyroSensor); //Calibrate gyro sensor
	ClearTimer(T1);

	adjustedTarget = ADJUST_M * turnDirection - ADJUST_B; //scale target angle linearly
	float turn = 100.0; //default pwr for drive train motors

	while(abs(remainingTurn) > TURN_THRESHOLD)
	{
		remainingTurn = adjustedTarget - gCurrTotalMove; //find # of degrees left to turn
		gCurrTotalMove += getAngleChange();
		error = adjustedTarget - gCurrTotalMove;
		turn = error * speedKonstant; //find pwr for DT motors

		//apply calculated turn pwr to DT motors
		//Use right side with +target
		if(turnDirection > 0)
		{
			motor[rightDrive] = turn;
		}
		//Use the left side with -target
		else
		{
			motor[leftDrive] = turn;
		}

		wait10Msec(1);
	}

	//done turning
	stopDriveTrain();
	resetGlobVars();
}


//-------------------------------AUTO ARM--------------------------------
/**************************************
** scoreAutoArm moves the auto arm   **
** to score on the right, starting   **
** from initial position.            **
***************************************/
void scoreAutoArm()
{
	servo[autoServo] = 160;
	wait10Msec(50);
	servo[autoServo] = 15;
	wait10Msec(50);
}


#endif;
