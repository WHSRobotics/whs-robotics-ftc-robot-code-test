#ifndef GYRO_HEADER1.H;
#define GYRO_HEADER1.H;


#include "hitechnic-gyro.h"



//Gyro variables
typedef struct
{
	bool isMUX; //check if connected to SMUX
	tMUXSensor MUXPort; //if sensor connected to SMUX
	tSensors NXTPort; //if sensor connected directly to NXT
	float DEFAULT_VAL; //const; generic value for initialization that's greater than 0
	float MILLISECOND; //const; num of Msec in 1 sec
	float ADJUST_M; //const; slope of linear equation to scale target angle
	float ADJUST_B; //const; y-intercept of linear equation to scale target angle
	float TURN_THRESHOLD; //const; stop turning when <1 degree left to turn
	float currentValue; //current value of adjusted gyro reading (w/o BIAS)
	float angleChange; //amt of change in angle turned
	float timeChange; //amt of change in time (sec)
	float currTotalMove; //amt turned already
	float remainingTurn; //amt of turn remaining
	float error;
	float adjustedTarget; //adjusted amt of turn remaining
	float reading;
	float turn;
}tGyro;


/**************************************
** resetGlobalVars resets the global **
** variables to their initial values **
** for gyro-dependent turn functions **
***************************************/
void resetGlobalVars(tGyro gyro)
{
	gyro.currentValue = 0.0;
	gyro.angleChange = 0.0;
	gyro.timeChange = 0.0;
	gyro.currTotalMove = 0.0;
	gyro.remainingTurn = gyro.DEFAULT_VAL;
	gyro.error = 0.0;
	gyro.adjustedTarget = 0.0;
	gyro.reading = 0.0;
}


void initGlobalVars(tGyro gyro, tMUXSensor inputMUX)
{
	gyro.isMUX = true;
	gyro.MUXPort = inputMUX;
	gyro.DEFAULT_VAL = 42.0; //generic value for initialization that's greater than 0
	gyro.MILLISECOND = 1000.0; //num of Msec in 1 sec
	gyro.ADJUST_M = 1.0; //slope of linear equation to scale target angle
	gyro.ADJUST_B = 7.0; //y-intercept of linear equation to scale target angle
	gyro.TURN_THRESHOLD = 1; //stop turning when <1 degree left to turn
	resetGlobalVars(gyro);
}


void initGlobalVars(tGyro gyro, tSensors inputNXT)
{
	gyro.isMUX = false;
	gyro.NXTPort = inputNXT;
	gyro.DEFAULT_VAL = 42.0; //generic value for initialization that's greater than 0
	gyro.MILLISECOND = 1000.0; //num of Msec in 1 sec
	gyro.ADJUST_M = 1.0; //slope of linear equation to scale target angle
	gyro.ADJUST_B = 7.0; //y-intercept of linear equation to scale target angle
	gyro.TURN_THRESHOLD = 1; //stop turning when <1 degree left to turn
	resetGlobalVars(gyro);
}


/**************************************
**  getAngleChange gives an updated  **
**  change in angle                  **
***************************************/
float getAngleChange(tGyro gyro)
{
	if(gyro.isMUX)
	{
		gyro.reading = HTGYROreadCal(gyro.MUXPort);
		gyro.currentValue = HTGYROreadRot(gyro.MUXPort);//gyroReading - BIAS;
	}
	else
	{
		gyro.reading = HTGYROreadCal(gyro.NXTPort);
		gyro.currentValue = HTGYROreadRot(gyro.NXTPort);
	}
	gyro.timeChange = time1[T1]/gyro.MILLISECOND; //change in time (sec)

	ClearTimer(T1);

	gyro.angleChange = gyro.currentValue * gyro.timeChange;
	return gyro.angleChange;
}


/*****************************************
**  getCurrTotalMove gives a current    **
**  running total of turn for the gyro  **
******************************************/
float getCurrTotalMove(tGyro gyro, float currTotal)
{
	currTotal += getAngleChange(gyro);
	return currTotal;
}

float updateTurn(tGyro gyro, float pwr)
{
	gyro.remainingTurn = gyro.adjustedTarget - gyro.currTotalMove; //find # of degrees left to turn
	gyro.currTotalMove += getAngleChange(gyro);
	gyro.error = gyro.adjustedTarget - gyro.currTotalMove;
	gyro.turn = gyro.error * pwr; //find pwr for DT motors
	return gyro.turn;
}

void calibrateGyro(tGyro gyro)
{
	if(gyro.isMUX)
	{
		HTGYROstartCal(gyro.MUXPort); //Calibrate gyro sensor
	}
	else
	{
		HTGYROstartCal(gyro.NXTPort);
	}
	ClearTimer(T1);
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
/*void gyroCenterPivot(tGyro gyro, int turnDirection, int speedKonstant)
{
	//Initialization
	calibrateGyro(gyro);

	gyro.adjustedTarget = gyro.ADJUST_M * turnDirection - gyro.ADJUST_B; //scale target angle linearly
	float turn = 100.0;  //default pwr for drive train motors

	while(abs(remainingTurn) > TURN_THRESHOLD) //while significantly turning
	{
		gyro.updateTurn();

		//apply calculated turn pwr to DT motors
		motor[driveLeft] = turn;
		motor[driveRight] = -turn;

		wait10Msec(1);
	}

	stopDriveTrain();
	resetGlobVars();
}*/

#endif
