#ifndef ARPS_FUNCTIONS_SWEDR.H;
#define ARPS_FUNCTIONS_SWEDR.H;

///////////////////////////INCLUDES////////////////////////////
#include "auto_globVars_swedr.h" //Header file with constants and global variables

/**********************************
** WHS Robotics  |  FTC Team 542 **
** Block Party! 2013-2014 Season **
** Autonomous (ARPS) V4          **
** Functions                     **
***********************************/

//-----------------BASE FUNCTIONS------------------
/**************************************
** magnitudeCalc calculates distance **
** or magnitude given x and y values **
***************************************/
float magnitudeCalc(float inputX, float inputY)
{
	return sqrt( pow(inputX, 2) + pow(inputY, 2) ) < 128.0
	? sqrt( pow(inputX, 2) + pow(inputY, 2) )
: 128.0;
}


/**************************************
**  simpleMotor specifies movement   **
**  explicity by parameters that     **
**  control direction and power      **
*--------------------------------------
* Parameters:
* tMotor motorName - specifies motor to control
* TServoIndex servoName - specifies servo to control
* int power - specifies motor velocity
* int angle - specifies servo swivel direction
* int initServoPos - allows calibration of servo swivel range
***************************************/
void simpleMotor(tMotor motorName, TServoIndex servoName, int power, int angle, int initServoPos)
{
	if(angle > 180)
	{
		servo[servoName] = (angle - 180) * SERVO_MAP_DEG + initServoPos;
		motor[motorName] = -power;
	}
	else
	{
		servo[servoName] = angle * SERVO_MAP_DEG + initServoPos;
		motor[motorName] = power;
	}
}


/**************************************
**  piMotor specifies movement       **
**  implicitly by translation vector **
**  components representing velocity **
*--------------------------------------
* Parameters:
* tMotor motorName - specifies motor to control
* TServoIndex servoName - specifies servo to control
* float inputY - specifies y component of velocity vector
* float inputX - specifies x component of velocity vector
* int initServoPos - allows calibration of servo swivel range
***************************************/
void piMotor(tMotor motorName, TServoIndex servoName, float inputY, float inputX, int initServoPos)
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
* float turnRadius - specifies radius of path in inches
* float arcAngle - distance to move in degrees
* float angVel - influences tangential velocity of robot, viable values(-256,256)
***************************************/
void moveArc(float turnRadius, float arcAngle, float angVel)
{
	float angSclr = angVel / (2.0 * HALF_WIDTH_X);
	float targetArcY1 = (turnRadius + HALF_WIDTH_X) * arcAngle * PI/180.0 * INCH_ENCODERVALUE;
	float targetArcY2 = (turnRadius - HALF_WIDTH_X) * arcAngle * PI/180.0 * INCH_ENCODERVALUE;

	float velX = angSclr * HALF_LENGTH_Y;
	float velLY = angSclr * (turnRadius + HALF_WIDTH_X);
	float velRY = angSclr * (turnRadius - HALF_WIDTH_X);

	nMotorEncoder[sweFL] = 0;
	nMotorEncoder[sweBL] = 0;
	nMotorEncoder[sweFR] = 0;
	nMotorEncoder[sweBR] = 0;

	nMotorEncoderTarget[sweFL] = targetArcY1;
	nMotorEncoderTarget[sweBL] = targetArcY1;
	nMotorEncoderTarget[sweFR] = targetArcY2;
	nMotorEncoderTarget[sweBR] = targetArcY2;

	piMotor(sweFL, swiFL, velLY, -velX, 0);
	piMotor(sweBL, swiBL, velLY, velX, -20);
	piMotor(sweFR, swiFR, velRY, -velX, 0);
	piMotor(sweBR, swiBR, velRY, velX, 0);

	while((nMotorRunState[sweFL] != runStateIdle)
		&& (nMotorRunState[sweBL] != runStateIdle)
	&& (nMotorRunState[sweFR] != runStateIdle)
	&& (nMotorRunState[sweBR] != runStateIdle))
	{
	}

	stopDriveTrain();
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
void moveStraight(float distanceInches, int power)
{
	int targetDistance = distanceInches * INCH_ENCODERVALUE;

	nMotorEncoder[sweFR] = 0;
	nMotorEncoderTarget[sweFR] = targetDistance;

	//nMotorEncoderTarget[sweFR] = targetDistance;

	//servo[swiFL] = dirAngle * SERVO_MAP_DEG + 30;
	//servo[swiBL] = dirAngle * SERVO_MAP_DEG -20;
	//servo[swiFR] = dirAngle * SERVO_MAP_DEG;
	//servo[swiBR] = dirAngle * SERVO_MAP_DEG -40;

	//wait1Msec(1000);

	motor[sweFL] = power;
	motor[sweBL] = power;
	motor[sweBR] = power;
	motor[sweFR] = power;

	while(nMotorEncoder[sweFR] < targetDistance)
	{
		writeDebugStreamLine("%d", nMotorEncoder[sweFR]);
	}

	motor[sweFR] = 0;
	motor[sweFL] = 0;
	motor[sweBR] = 0;
	motor[sweBL] = 0;
	//stopDriveTrain();
}


/**************************************
** handArmMaintain prevents the hang **
** arm from interfering with scoring **
***************************************/
void hangArmMaintain()
{
	motor[hangmanMot] = -30;
}


/**************************************
** moveArm sets both arm motors to   **
** a specific power.                 **
***************************************/
void moveArm(int power)
{
	motor[armL] = power;
	motor[armR] = power;
}

//--//
//--------------------RESETS-------------------------

/**************************************
** resetBucket closes the intake     **
** bucket to initial position.       **
***************************************/
void resetBucket()
{
	servoTarget[dropbox] = 255;
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

		wait10Msec(1);
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