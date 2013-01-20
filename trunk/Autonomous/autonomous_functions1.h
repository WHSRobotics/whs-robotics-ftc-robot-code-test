#ifndef AUTONOMOUS_FUNCTIONS1.H;
#define AUTONOMOUS_FUNCTIONS1.H;

/**********************************
** WHS Robotics  |  FTC Team 542 **
** Ring It Up! 2012-2013 Season  **
** Autonomous Program 1.0        **
** Functions                     **
***********************************/



///////////////////////////INCLUDES////////////////////////////
#include "common.h" //header file for common stuf
#include "autonomous_constants_globVars.h" //Header file with constants and global variables
#include "hitechnic-gyro.h" //driver for gyro
#include "hitechnic-touchmux.h"  //header file for Windsor's TUX


/////////////////////////FUNCTIONS/////////////////////////////
/**************************************
** resetGlobVars resets the global   **
** variables to their initial values **
** for gyro-dependent turn functions **
***************************************/
void resetGlobVars()
{
  currentValue = 0.0;
	angleChange = 0.0;
	timeChange = 0.0;
	gCurrTotalMove = 0.0;
	sCurrTotalTurn = 0.0;
	remainingTurn = DEFAULT_VAL;
	error = 0.0;
	gyroReading = 0.0;
	adjustedTarget = 0.0;
}


/************************************************
** resetFlags moves flags down and stops them  **
*************************************************/
void resetFlags()
{
  //move flags down
  motor[flagLeft] = -50;
  motor[flagRight] = -50;

  wait10Msec(50);

  //stop flags
  motor[flagLeft] = 0;
  motor[flagRight] = 0;
}



/*************************************************
** resetArm initializes arm to lowest position  **
**************************************************/
void resetArm()
{
  //Briefly lift arm
	motor[armLeft] = 10;
	motor[armRight] = 10;
	wait10Msec(25);
	motor[armLeft] = 0;
	motor[armRight] = 0;

	//Lower arm until lowest (when touch sensor pressed)
  while(HTTMUXisActive(TUX, 1) == false)
  {
		motor[armLeft] = -7;
		motor[armRight] = -7;
	}

	wait1Msec(100);
	//stop arm
	motor[armLeft] = 0;
	motor[armRight] = 0;
}


/*******************************************
** stopArm sets the arm motors to 0 power **
********************************************/
void stopArm()
{
  motor[armLeft] = 0;
	motor[armRight] = 0;
}


/*************************************************
** moveArm sets the arm motors at a given power **
**************************************************/
void moveArm(int pwr)
{
  motor[armLeft] = pwr;
	motor[armRight] = pwr;
}



/**************************************
** stopDriveTrain sets the drive     **
** train motors to 0 power           **
***************************************/
void stopDriveTrain()
{
  motor[driveLeft] = 0;
	motor[driveRight] = 0;
}



/**************************************
**  getAngleChange gives an updated  **
**  change in angle                  **
***************************************/
float getAngleChange()
{
	gyroReading = HTGYROreadCal(gyroRobot);
	currentValue = HTGYROreadRot(gyroRobot);//gyroReading - BIAS;
	timeChange = time1[T1]/MILLISECOND; //change in time (sec)

	ClearTimer(T1);

	angleChange = currentValue * timeChange;
	return angleChange;
}


/*****************************************
**  getCurrTotalMove gives a current    **
**  running total of turn for the gyro  **
******************************************/
float getCurrTotalMove(float currTotal)
{
	currTotal += getAngleChange();
	return currTotal;
}


/***************************************
**  gyroCenterPivot turns the robot   **
**  accurately using the gyro sensor. **
**  Turns at a certain speed until it **
**  gets to turnDirection.            **
*--------------------------------------*
* Parameters:
* int turnDirection - Num degrees to turn to
* int speedKonstant - Speed to turn at
****************************************/
//Should add a parameter to determine which way to pivot (left or right)
void gyroCenterPivot(int turnDirection, int speedKonstant)
{
  //Initialization
	HTGYROstartCal(gyroRobot); //Calibrate gyro sensor
	ClearTimer(T1);

	adjustedTarget = ADJUST_M * turnDirection - ADJUST_B; //scale target angle linearly
	float turn = 100.0;  //default pwr for drive train motors

	while(abs(remainingTurn) > TURN_THRESHOLD) //while significantly turning
	{
		remainingTurn = adjustedTarget - gCurrTotalMove; //find # of degrees left to turn
		gCurrTotalMove += getAngleChange();
		error = adjustedTarget - gCurrTotalMove;
		turn = error * speedKonstant; //find pwr for DT motors

	  //apply calculated turn pwr to DT motors
		motor[driveLeft] = turn;
		motor[driveRight] = -turn;

		wait10Msec(1);
	}

  stopDriveTrain();
  resetGlobVars();
}


/**************************************
**  moveStraight moves the robot
**  forward a specified distance at a
**  specified power using encoders
*--------------------------------------
* Parameters:
* float distanceInches - distance to move in inches
* int pwr - motor power for drive train
***************************************/
void moveStraight(float distanceInches, int pwr)
{
  //convert given inches to encoder values
	float targetDistance = distanceInches * INCH_ENCODERVALUE;

	//adjust pwr to drive train motors
	float pwrDriveLeft = pwr;
	float pwrDriveRight = pwr;

	//reset drive train motor encoders
	nMotorEncoder[driveLeft] = 0;
	nMotorEncoder[driveRight] = 0;

	//set DT motor encoders to converted inches
	nMotorEncoderTarget[driveLeft] = targetDistance;
	nMotorEncoderTarget[driveRight] = targetDistance;

	//set DT motors to adjusted powers
	motor[driveLeft] = pwrDriveLeft;
	motor[driveRight] = pwrDriveRight;

	float scurrentValue = 0.0;
	//while DT motors are still running (not stopped)
	while(nMotorRunState[driveLeft] != runStateIdle && nMotorRunState[driveRight] != runStateIdle)
	{
		scurrentValue = HTGyroreadRot(gyroRobot);
		if(scurrentValue < -0.5)
		{
			pwrDriveLeft += 1;
			//pwrDriveRight -= 1;
			motor[driveLeft] = pwrDriveLeft;
			//motor[driveRight] = pwrDriveRight;
		}
		else if(scurrentValue > 0.5)
		{
			pwrDriveRight += 1;
			//pwrDriveLeft -= 1;
			//motor[driveLeft] = pwrDriveLeft;
			motor[driveRight] = pwrDriveRight;
		}
		else if(pwrDriveLeft >= pwr || pwrDriveRight >= pwr)
		{
			pwrDriveLeft -= 1;
			pwrDriveRight -= 1;
			motor[driveLeft] = pwrDriveLeft;
			motor[driveRight] = pwrDriveRight;
		}
		/*sCurrTotalTurn += getAngleChange();
		wait10Msec(1);*/
	  // do not continue
	}

	/*ClearTimer(T1);
	scurrentValue = HTGYROreadRot(gyroRobot);//gyroReading - BIAS;
	float stimeChange = time1[T1]/MILLISECOND; //change in time (sec)

	ClearTimer(T1);

	float sangleChange = scurrentValue * stimeChange;

	PlayTone(440,40);
	gyroCenterPivot(-sangleChange, 50);*/
	/*pwrDriveLeft = (PWR_ADJUST/2);
	pwrDriveRight = -(PWR_ADJUST/2);

	motor[driveLeft] = pwrDriveLeft;
	motor[driveRight] = pwrDriveRight;

	wait1Msec(500);*/

	stopDriveTrain();
}


/******************************************
**  moveArm moves the arm for a specified
**  power for a specified time (Msec)
*------------------------------------------
* Parameters:
* int pwr - power for the arm motors
* int msec - num of Msec to power arm motors
*******************************************/
void moveArm(int pwr, int msec)
{
  //Move the arm at full power 5% of the time (majorMsec)
  //and gradually ramp down power 95% of the time (minorMsec)
	float majorMsec = msec * MAJOR_MSEC_PERCENT;
	float minorMsec = msec * MINOR_MSEC_PERCENT;

  float newPwr = 0.0; //pwr for minorMsec
  float newMsec = 0.0; //keep track of Msec passed in minorMsec

  //Major Msec Stage:
  //Move arm at full pwr for majorMsec
  moveArm(pwr);
  wait1Msec(majorMsec);

  //Minor Msec Stage:
  //Move arm at gradually ramping pwr for minorMsec
  while(newMsec <= minorMsec)
  {
    //ramp pwr linearly
    newPwr = -(pwr/minorMsec)*newMsec + pwr;

    //apply new ramped pwr to arm
    moveArm(newPwr);

    //1 Msec passes
    wait1Msec(1);
    newMsec += 1.0;
  }

  stopArm();
}


/*void moveArm(int pwr, int msec)
{
	float majorMsec = msec * 0.3;
	float minorMsec = msec * 0.7;

	float newPwr = 0.0;
	float newMsec = 0.0;
	float increment = (0.09 * pwr)/minorMsec;
	//float ratioChange = 0.0;
	//float pwrRatio = 1.0;
	//float msecRatio = 0.0;

	motor[armLeft] = pwr;
	motor[armRight] = pwr;

	wait1Msec(majorMsec);

	while(newMsec < minorMsec)
	{
		newPwr = (0.09 * pwr) - (newMsec * increment);
		motor[armLeft] = newPwr;
		motor[armRight] = newPwr;
		wait1Msec(1);
		newMsec += 1.0;
	}
	motor[armLeft] = 0;
	motor[armRight] = 0;
	for(int count = 0; count <= 10; count++)
	{
		ratioChange = count/10.0;
		pwrRatio -= ratioChange;
		msecRatio += ratioChange;
		newPwr = pwr*pwrRatio;
		newMsec = minorMsec*msecRatio;
		motor[armLeft] = newPwr;
		motor[armLeft] = newPwr;
		wait1Msec(newMsec);
	}

	motor[armLeft] = 0;
	motor[armRight] = 0;
}*/



#endif;
