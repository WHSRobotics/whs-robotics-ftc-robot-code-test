#ifndef ARPS_FUNCTIONS_SWE.H;
#define ARPS_FUNCTIONS_SWE.H;

///////////////////////////INCLUDES////////////////////////////
#include "auto_globVars_swedr." //Header file with constants and global variables

/**********************************
** WHS Robotics  |  FTC Team 542 **
** Block Party! 2013-2014 Season **
** Autonomous (ARPS) V4          **
** Functions                     **
***********************************/

//-----------------BASE CONTROLS------------------
/**************************************
** setAngle sets all swivel servos   **
** to a specific angle in radians    **
***************************************/
void setAngle(float angle)
{
	servo[swiFL] = angle * SERVO_MAP;
	servo[swiFR] = angle * SERVO_MAP;
	servo[swiBR] = angle * SERVO_MAP;
	servo[swiBL] = angle * SERVO_MAP - 20;
}

void piMotor(tMotor motorName, TServoIndex servoName, float inputY, float inputX, int initServoPos)
{
	if((magnitudeCalc(inputY, inputX) > LOW_THRESH) && (magnitudeCalc(inputY, inputX) <= 128.0))
	{
		if(atan2(inputY, inputX) < 0)
		{
			servo[servoName] = (atan2(inputY, inputX) + PI) * SERVO_MAP + initServoPos;
			motor[motorName] = -magnitudeCalc(inputY, inputX) * JOY_MAP;
		}
		else
		{
			servo[servoName] = atan2(inputY, inputX) * SERVO_MAP + initServoPos;
			motor[motorName] = magnitudeCalc(inputY, inputX)* JOY_MAP;
		}
	}
	else
	{
		servo[servoName] = PI/2.0 * SERVO_MAP + initServoPos;
		motor[motorName] = 0;
	}
}

//-----------------MOVES AND STOPS------------------
/**************************************
** stopDriveTrain sets both drive    **
** train motors to a specific power. **
***************************************/
void stopDriveTrain()
{
	servo[swiFL] = 127;
	servo[swiBL] = 107;
	servo[swiFR] = 127;
	servo[swiBR] = 127;
	motor[sweFL] = STOP;
	motor[sweBL] = STOP;
	motor[sweFR] = STOP;
	motor[sweBR] = STOP;
}

/**************************************
**  moveArc moves the robot          **
**  on a specificed circle at        **
**  a specified power using encoders **
*--------------------------------------
* Parameters:
* float turnRadius - specifies radius of path
* float arcAngle - distance to move in degrees
* int pwr - motor power for drive train
***************************************/
void moveArc(float turnRadius, float arcAngle, int pwr)
{
	//specify swivel angles for turn radius
	//

	float scaledY1 = -diffY1Input * TANK_SPEED_SCALE;
	float scaledY2 = -diffY2Input * TANK_SPEED_SCALE;
	float velX = HALF_LENGTH_Y * (scaledY1 - scaledY2)/(2.0*HALF_WIDTH_X);

	piMotor(sweFL, swiFL, scaledY1, -velX, 0);
	piMotor(sweBL, swiBL, scaledY1, velX, -20);
	piMotor(sweFR, swiFR, scaledY2, -velX, 0);
	piMotor(sweBR, swiBR, scaledY2, velX, 0);
}

/**************************************
**  moveStraight moves the robot     **
**  forward a specified distance at  **
**  a specified power using encoders **
*--------------------------------------
* Parameters:
* float dirAngle - direction of movement in degrees
* float distanceInches - distance to move in inches
* int pwr - motor power for drive train
***************************************/
void moveStraight(float dirAngle, float distanceInches, int pwr)
{
	//set angle
	//run motors
	//stop motors

	float targetDistance = distanceInches*INCH_ENCODERVALUE;
	float leftPwr = pwr;
	float rightPwr = pwr;

	nMotorEncoder[leftDrive] = 0;
	nMotorEncoder[rightDrive] = 0;

	nMotorEncoderTarget[leftDrive] = targetDistance;
	nMotorEncoderTarget[rightDrive] = targetDistance;

	motor[leftDrive] = leftPwr;
	motor[rightDrive] = rightPwr;

	while(nMotorRunState[leftDrive] != runStateIdle && nMotorRunState[rightDrive] != runStateIdle)
	{
	}

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


//--------------------RESETS-------------------------

/**************************************
** resetBucket closes the intake     **
** bucket to initial position.       **
***************************************/
void resetBucket()
{
	servoTarget[intakeServo] = 80;
}



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
	adjustedTarget = 0.0;
}


/**************************************
** resetHang drops the hang arms     **
** to initial position.              **
***************************************/
void resetHang()
{
	servoTarget[hangServo1] = 60;
	servoTarget[hangServo2] = 180;
}



void resetFlag()
{
	servo[flagServo] = 120;
}


//------------------------------GYRO---------------------
/**************************************
**  getAngleChange gives an updated  **
**  change in angle                  **
***************************************/
float getAngleChange()
{
	currentValue = HTGYROreadRot(gyroSensor);//gyroReading - BIAS;
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
	HTGYROstartCal(gyroSensor); //Calibrate gyro sensor
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
		motor[leftDrive] = turn;
		motor[rightDrive] = -turn;

		wait10Msec(1);
	}

  stopDriveTrain();
  resetGlobVars();
}


/***************************************
**  gyroSidePivot turns the robot     **
**  accurately, driving on one side		**
**  using the gyro sensor.   					**
**  Turns at a certain speed until it **
**  gets to turnDirection.            **
*--------------------------------------*
* Parameters:
* int turnDirection - Num degrees to turn to
										- Positive number of degrees turns the robot with the right
										- Negative number of degrees turns the robot with the left
* int speedKonstant - Speed to turn at
										- Positive number of degrees turns the robot by moving the motors forward
										- Negative number of degrees turns the robot by moving the motors backwards
****************************************/
void gyroSidePivot(int turnDirection, int speedKonstant)
{
  //Initialization
	HTGYROstartCal(gyroSensor); //Calibrate gyro sensor
	ClearTimer(T1);

	adjustedTarget = ADJUST_M * turnDirection - ADJUST_B; //scale target angle linearly
	float turn = 100.0;  //default pwr for drive train motors

	while(abs(remainingTurn) > TURN_THRESHOLD) //while significantly turning
	{
		remainingTurn = adjustedTarget - gCurrTotalMove; //find # of degrees left to turn
		gCurrTotalMove += getAngleChange();
		error = adjustedTarget - gCurrTotalMove;
		turn = error * speedKonstant; //find pwr for DT motors

	  ////apply calculated turn pwr to DT motors
		//Use the right side of the DT with a positive target
		if(turnDirection > 0)
		{
		  motor[rightDrive] = turn;
		}
		//Use the left side of the DT with a negative target
		else
		{
			motor[leftDrive] = turn;
		}

		wait10Msec(1);
	}

  stopDriveTrain();
  resetGlobVars();
}


/***************************************
**  gyroCurve turns the robot         **
**  accurately, curving	using the     **
**  gyro and moving forward   				**
**  Turns at a certain speed until it **
**  gets to turnDirection.            **
**  Can specify speed of minor motor. **
*--------------------------------------*
* Parameters:
* int turnDirection - Num degrees to turn to
										- Positive number of degrees turns the robot with the right
										- Negative number of degrees turns the robot with the left
* int speedKonstant - Speed for major turning motor to turn at
										- Positive number of degrees turns the robot by moving the motors forward
										- Negative number of degrees turns the robot by moving the motors backwards
* int subPwr        - Speed for minor turning motor to turn at
****************************************/
void gyroCurve(int turnDirection, int speedKonstant, int subPwr)
{
  //Initialization
	HTGYROstartCal(gyroSensor); //Calibrate gyro sensor
	ClearTimer(T1);

	adjustedTarget = ADJUST_M * turnDirection - ADJUST_B; //scale target angle linearly
	float turn = 100.0;  //default pwr for drive train motors
	float subturn = 100.0;
	float subRatio = subPwr/speedKonstant;

	while(abs(remainingTurn) > TURN_THRESHOLD) //while significantly turning
	{
		remainingTurn = adjustedTarget - gCurrTotalMove; //find # of degrees left to turn
		gCurrTotalMove += getAngleChange();
		error = adjustedTarget - gCurrTotalMove;
		turn = error * speedKonstant; //find pwr for DT motors
		subturn = turn * subRatio;


	  ////apply calculated turn pwr to DT motors
		//Use the right side of the DT with a positive target
		if(turnDirection < 0)
		{
		  motor[rightDrive] = turn;
		  motor[leftDrive] = subturn;
		}
		//Use the left side of the DT with a negative target
		else
		{
			motor[leftDrive] = turn;
			motor[rightDrive] = subturn;
		}

		wait10Msec(50);
	}

  stopDriveTrain();
  resetGlobVars();
}



//-------------------AUTO ARM------------------
void dropTheBlock()
{
	//servo[dropbox] = 160;
	motor[intakeL] = INTAKE_R;
	motor[intakeR] = INTAKE_R;
	wait10Msec(50);
	//servo[dropbox] = 15;
	motor[intakeL] = MAX;
	motor[intakeR] = MAX;
	wait10Msec(50);
}



#endif;
