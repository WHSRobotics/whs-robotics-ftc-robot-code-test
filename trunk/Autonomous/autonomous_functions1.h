#ifndef AUTONOMOUS_FUNCTIONS1.H;
#define AUTONOMOUS_FUNCTIONS1.H;

#include "autonomous_constants_globVars.h" //Include header file with the constants and global variables for the autonomous
#include "hitechnic-gyro.h" //Include driver for gyro


///////////////FUNCTIONS///////////////
/////Resets the global variables to their initial values
void resetGlobVars()
{
  currentValue = 0.0;
	angleChange = 0.0;
	timeChange = 0.0;
	currTotalMove = 0.0;
	remainingTurn = DEFAULT_VAL;
	error = 0.0;
	gyroReading = 0.0;
	adjustedTarget = 0.0;
}


void stopDriveTrain()
{
  motor[driveLeft] = 0;
	motor[driveRight] = 0;
}


////////Gyro accurate turn functions
////gives an updated change in angle
float getAngleChange()
{
	gyroReading = HTGYROreadCal(3);
	currentValue = HTGYROreadRot(3);//gyroReading - BIAS;
	timeChange = time1[T1]/1000.0;
	ClearTimer(T1);
	angleChange = currentValue * timeChange;
	return angleChange;
}


////gives a current running total of turn for the gyro
float getCurrTotalMove()
{
	currTotalMove += getAngleChange();
	return currTotalMove;
}


////Actual turn task
////Turn at a certain speed (determined by speedK) until get to turnDirection
//** should add a parameter to determine which way to pivot (left or right)
void gyroCenterPivot(int turnDirection, int speedKonstant)
{
	HTGYROstartCal(3);
	ClearTimer(T1);
	adjustedTarget = ADJUST_M * turnDirection - ADJUST_B;
	float turn = 100.0;
	while(abs(remainingTurn) > 1)
	{
		remainingTurn = adjustedTarget - currTotalMove;
		error = adjustedTarget - getCurrTotalMove();
		turn = error * speedKonstant;
		motor[driveLeft] = turn;
		motor[driveRight] = -turn;
		wait10Msec(1);
	}
  stopDriveTrain();
  resetGlobVars();
}


////Move forward a specified distance at a specified power
///Parameters: distanceInches - distance to move in inches
///            pwr - motor power for drive train
void moveStraight(float distanceInches, int pwr)
{
	float targetDistance = distanceInches * INCH_ENCODERVALUE;
	float pwrDriveLeft = pwr + (PWR_ADJUST/2);
	float pwrDriveRight = pwr - (PWR_ADJUST/2);

	nMotorEncoder[driveLeft] = 0;
	nMotorEncoder[driveRight] = 0;

	nMotorEncoderTarget[driveLeft] = targetDistance;
	nMotorEncoderTarget[driveRight] = targetDistance;

	motor[driveLeft] = pwrDriveLeft;
	motor[driveRight]= pwrDriveRight;


	while(nMotorRunState[driveLeft] != runStateIdle && nMotorRunState[driveRight] != runStateIdle)  // while Motor B is still running (hasn't reached target yet):
		{
		  // do not continue
		}
	stopDriveTrain();
}


////Move arm by a specified angle at a specified power.
////Moves motor in quick, small increments until angle is reached.
///Parameters: angle - angle to move the arm
///            pwr - power for arm motors
void moveArm(float angle, int pwr)
{
	int numIncrements = 0; //number of times to loop
	int increment = 0; //increment per loop

	//set # of increments and amt of increment based on odd or even angle
	if((angle%2) == 0) //if angle is even
	{
		numIncrements = angle/2; //loop half the number of degrees in angle
		increment = 2; //increment by 2
	}
	else //if angle is odd
	{
		numIncrements = angle; //loop by number of degrees
		increment = 1; //increment by 1
	}

	int count = 0; //keep count of the number of times looped so far

	while(count < numIncrements)
	{
		nMotorEncoder[armLeft] = 0; //reset encoder

		nMotorEncoderTarget[armLeft] = increment; //set target to increment

		//move arm at given power
		motor[armLeft] = pwr;
		motor[armRight] = pwr;

		while(nMotorRunState[armLeft] != runStateIdle)  // while armLeft is still moving
		{
		  // do not continue
		}
		//stop arm (is this necessary? o.0)
		motor[armLeft] = 0;
		motor[armRight] = 0;

		count++; //add to the # of times this loop has been carried out
		wait10Msec(5); //briefly wait
	}
}


#endif;
