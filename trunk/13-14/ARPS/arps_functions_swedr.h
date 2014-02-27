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

//--------------TASKS-----------------
task Hangman()
{
	while(true)
	{
		motor[hangmanMot] = HANGMAN_DOWN;
	}
}

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


void setServoAngle(float angle)
{
	if(angle > 180)
	{
		servo[swiFL] = FL_SERVO_MAP * (angle - 180);
		servo[swiBL] = BL_SERVO_MAP * (angle - 180) + 34;
		servo[swiFR] = FR_SERVO_MAP * (angle - 180) + 30;
		servo[swiBR] = BR_SERVO_MAP * (angle - 180) + 30;
	}
	else
	{
		servo[swiFL] = FL_SERVO_MAP * angle;
		servo[swiBL] = BL_SERVO_MAP * angle + 34;
		servo[swiFR] = FR_SERVO_MAP * angle + 30;
		servo[swiBR] = BR_SERVO_MAP * angle + 30;
	}
}


void runDriveTrain(float power)
{
	motor[sweFL] = power;
	motor[sweBL] = power;
	motor[sweFR] = power;
	motor[sweBR] = power;
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
void simpleMotor(tMotor motorName, TServoIndex servoName, float power, float angle, int initServoPos, float specServoMap)
{
	float servoAng;
	float motPow;
	if(angle > 180)
	{
		servoAng = specServoMap * (angle - 180) - initServoPos;
		motPow = power;
		setServoAngle(servoAng);
	}
	else
	{
		servoAng = specServoMap * angle - initServoPos;
		motPow = -power;
		setServoAngle(servoAng);
	}
	wait1Msec(5000);
	runDriveTrain(motPow);

}


/**************************************
**  piServo specifies movement       **
**  implicitly by translation vector **
**  components representing velocity **
*--------------------------------------
* Parameters:
* TServoIndex servoName - specifies servo to control
* float inputY - specifies y component of velocity vector
* float inputX - specifies x component of velocity vector
* int initServoPos - allows calibration of servo swivel range
***************************************/
void piServo(TServoIndex servoName, float inputY, float inputX, int initServoPos, float specServoMap)
{
	if(magnitudeCalc(inputY, inputX) > 15)
	{
		if(atan2(inputY, inputX) < 0)
		{
			servo[servoName] = (specServoMap * 180) - (initServoPos + ((atan2(inputY, inputX)+PI) * RAD_DEG * specServoMap));
		}
		else
		{
			servo[servoName] = (specServoMap * 180) - (initServoPos + (atan2(inputY, inputX) * RAD_DEG * specServoMap));
		}
	}
	else
	{
		servo[servoName] = 90.0 * specServoMap - initServoPos;
	}
}


/**************************************
**  piMotor specifies movement       **
**  implicitly by translation vector **
**  components representing velocity **
*--------------------------------------
* Parameters:
* tMotor motorName - specifies motor to control
* float inputY - specifies y component of velocity vector
* float inputX - specifies x component of velocity vector
***************************************/
void piMotor(tMotor motorName, float inputY, float inputX)
{
	if(magnitudeCalc(inputY, inputX) > 15)
	{
		if(atan2(inputY, inputX) < 0)
		{
			motor[motorName] = magnitudeCalc(inputY, inputX) * JOY_MAP;
		}
		else
		{
			motor[motorName] = -magnitudeCalc(inputY, inputX)* JOY_MAP;
		}
	}
	else
	{
		motor[motorName] = STOP;
	}
}



//-----------------MOVES AND STOPS------------------
/**************************************
** stopDriveTrain sets both drive    **
** train motors to a specific power. **
***************************************/
void stopDriveTrain()
{
	servo[swiFL] = 90 * FL_SERVO_MAP;
	servo[swiBL] = 90 * BL_SERVO_MAP + 34;
	servo[swiFR] = 90 * FR_SERVO_MAP + 30;
	servo[swiBR] = 90 * BR_SERVO_MAP + 30;
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
	float targetArcY1 = (turnRadius + HALF_WIDTH_X) * arcAngle / RAD_DEG * INCH_ENCODERVALUE;// * abs(angVel)/angVel;
	float targetArcY2 = (turnRadius - HALF_WIDTH_X) * arcAngle / RAD_DEG * INCH_ENCODERVALUE;// * abs(angVel)/angVel;

	float velX = angSclr * HALF_LENGTH_Y;
	float velLY = angSclr * (turnRadius + HALF_WIDTH_X);
	float velRY = angSclr * (turnRadius - HALF_WIDTH_X);

	nMotorEncoder[sweBL] = 0;
	nMotorEncoder[sweBR] = 0;

	piServo(swiFL, velLY, velX, 0, FL_SERVO_MAP);
	piServo(swiBL, velLY, -velX, -34, BL_SERVO_MAP);
	piServo(swiFR, velRY, velX, -30, FR_SERVO_MAP);
	piServo(swiBR, velRY, -velX, -30, BR_SERVO_MAP);

	wait1Msec(500);

	piMotor(sweFL, velLY, velX);
	piMotor(sweBL, velLY, -velX);
	piMotor(sweFR, velRY, velX);
	piMotor(sweBR, velRY, -velX);

	while((abs(nMotorEncoder[sweBR]) <= abs(targetArcY2)) || (abs(nMotorEncoder[sweBL]) <= abs(targetArcY1)))
	{
		//writeDebugStreamLine("BR: %f, BL: %f", nMotorEncoder[sweBR], nMotorEncoder[sweBL]);
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
void moveStraight(float dirAngle, float distanceInches, float power)
{
	int targetDistance = distanceInches * INCH_ENCODERVALUE;// * abs(power)/power;

	nMotorEncoder[sweBR] = 0;
	//nMotorEncoder[sweBR] = 0;
	//nMotorEncoder[sweFR] = 0;

	/*simpleMotor(sweFL, swiFL, power, dirAngle, 0, FL_SERVO_MAP);
	simpleMotor(sweBL, swiBL, power, dirAngle, -34, BL_SERVO_MAP);
	simpleMotor(sweFR, swiFR, power, dirAngle, -30, FR_SERVO_MAP);
	simpleMotor(sweBR, swiBR, power, dirAngle, -30, BR_SERVO_MAP);*/
	setServoAngle(dirAngle);
	wait1Msec(1000);
	runDriveTrain(-power);

	while(abs(nMotorEncoder[sweBR]) <= targetDistance)// || abs(nMotorEncoder[sweBR]) <= targetDistance)/* || (nMotorEncoder[sweFL] <= targetDistance)*/
	{
		setServoAngle(dirAngle);
		//writeDebugStreamLine("BL: %f, BR: %f", nMotorEncoder[sweBL], nMotorEncoder[sweBR]);
	}

	stopDriveTrain();
	wait1Msec(200);
}


/**************************************
** handArmMaintain prevents the hang **
** arm from interfering with scoring **
***************************************/
task hangArmMaintain()
{
	motor[hangmanMot] = -60;
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
/*float getAngleChange()
{
	currentValue = HTGYROreadRot(gyroSensor);//gyroReading - BIAS;
	timeChange = time1[T1]/MILLISECOND; //change in time (sec)

	ClearTimer(T1);

	angleChange = currentValue * timeChange;
	return angleChange;
}*/


/*****************************************
**  getCurrTotalMove gives a current    **
**  running total of turn for the gyro  **
******************************************/
//float getCurrTotalMove(float currTotal)
//{
//	currTotal += getAngleChange();
//	return currTotal;
//}


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
//void gyroCenterPivot(int turnDirection, int speedKonstant)
//{
//	//Initialization
//	HTGYROstartCal(gyroSensor); //Calibrate gyro sensor
//	ClearTimer(T1);

//	adjustedTarget = ADJUST_M * turnDirection - ADJUST_B; //scale target angle linearly
//	float turn = 100.0;  //default pwr for drive train motors

//	while(abs(remainingTurn) > TURN_THRESHOLD) //while significantly turning
//	{
//		remainingTurn = adjustedTarget - gCurrTotalMove; //find # of degrees left to turn
//		gCurrTotalMove += getAngleChange();
//		error = adjustedTarget - gCurrTotalMove;
//		turn = error * speedKonstant; //find pwr for DT motors

//		//apply calculated turn pwr to DT motors

//		wait10Msec(1);
//	}

//	stopDriveTrain();
//	resetGlobVars();
//}


//-------------------AUTO ARM------------------
task HoldBox()
{
	while(!boxOpen)
	{
		servo[dropbox] = 255;
	}
}


void dropTheBlock()
{
	boxOpen = true;
	StopTask(HoldBox);

	servo[dropbox] = BOX_OPEN;
	wait10Msec(90);
	servo[dropbox] = BOX_CLOSED;
	wait10Msec(60);
}
task RampArm()
{
	moveArm(90);
	wait1Msec(300);
	moveArm(0);
}
task ScoreArm()
{
	moveArm(100);
	wait1Msec(600);
	moveArm(0);
}
task AntiRat()
{
	while(true)
	{
		servo[antiRatchet] = AR_CLOSED;
	}
}


#endif;
