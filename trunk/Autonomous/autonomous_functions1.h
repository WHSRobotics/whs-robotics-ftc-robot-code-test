#ifndef AUTONOMOUS_FUNCTIONS1.H;
#define AUTONOMOUS_FUNCTIONS1.H;

///////////////FUNCTIONS///////////////

////////Gyro accurate turn functions
////gives an updated change in angle
float getAngleChange()
{
	gyroReading = HTGYROreadCal(3);
	currentValue = HTGYROreadRot(3);
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
void gyroCenterPivot(int turnDirection, int speedKonstant)
{
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
	motor[driveLeft] = 0;
	motor[driveRight] = 0;
	currentValue = 0.0;
	angleChange = 0.0;
	timeChange = 0.0;
	currTotalMove = 0.0;
	remainingTurn = 42.0;
	error = 0.0;
	gyroReading = 0.0;
	adjustedTarget = 0.0;
}

////Move forward a specified distance
void moveForward(float distanceInches)
{

}

#endif;
