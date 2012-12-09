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
	gyroReading = HTGYROreadCal(3); //this isn't necessary
	currentValue = HTGYROreadRot(3);
	timeChange = time1[T1]/MILLISECOND;
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
	adjustedTarget = ADJUST_M * turnDirection - ADJUST_B; //scale target using linear equation
	float turn = DEFAULT_VAL; //initialize turn to a value greater than 1
	while(abs(remainingTurn) > 1) //P controller while turning
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
void moveForward(float distanceInches, int motPower)
{
	nMotorEncoder[driveLeft] = 0;                // reset the Motor Encoder of Motor B
	nMotorEncoder[driveRight] = 0;

	nMotorEncoderTarget[driveLeft] = distanceInches;        // set the  target for Motor Encoder of Motor B to 360
	nMotorEncoderTarget[driveRight] = distanceInches;

	motor[driveLeft] = motPower;
	motor[driveRight]= motPower;

	while(nMotorRunState[driveLeft] != runStateIdle && nMotorRunState[driveRight] != runStateIdle)  // while Motor B is still running (hasn't reached target yet):
	{
	  // do not continue
	}

	stopDriveTrain();
}



#endif;
