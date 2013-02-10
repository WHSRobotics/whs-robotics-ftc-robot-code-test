#ifndef AUTONOMOUS_CONSTANTS_GLOBVARS.H;
#define AUTONOMOUS_CONSTANTS_GLOBVARS.H;

/**********************************
** WHS Robotics  |  FTC Team 542 **
** Ring It Up! 2012-2013 Season  **
** Autonomous Program 1.0        **
** Global Variables              **
***********************************/



///////////////////////////INCLUDES////////////////////////////
#include "hitechnic-sensormux.h"  //header file for SMUX
#include "hitechnic-irseeker-v2.h" //header file for IR seeker v2! :D
#include "hitechnic-gyro.h" //driver for gyro
#include "hitechnic-touchmux.h"  //header file for Windsor's TUX


///////////////////KONSTANTS///////////////////
////General KONSTANTS////
const float MILLISECOND = 1000.0; //number of milliseconds in one second
const float DEFAULT_VAL = 42.0; //generic value for initialization that's greater than 0

////Sensor Definitions////
///const tMUXSensor IRSensor = msensor_S2_3;

////Gyro KONSTANTS////
//gyroCenterPivot
const float LOW_TURK = 0.75; //turn konstant for low power
const float MID_TURK = 0.9; //turn konstant for mid power
const float HIGH_TURK = 10.0; //turn konstant for high power
const float ADJUST_M = 1.0; //slope of linear equation to scale target angle
const float ADJUST_B = 7.0; //y-intercept of linear equation to scale target angle
const int TURN_THRESHOLD = 1; //stop turning when <1 degree left to turn

////Drive Train KONSTANTS////
//moveStraight
const float INCH_ENCODERVALUE = 114.591559; //number of encoder values in one inch forward for a 4 inch wheel
																						//(number of encoder values in one rotation[1440])/(wheel diameter[4]*pi[3.14...])
const float PWR_ADJUST = 7.355;//3.9 //7.5

////Arm KONSTANTS////
//moveArm
const float MAJOR_MSEC_PERCENT = 0.05; //percent of Msec to run arm at full pwr
const float MINOR_MSEC_PERCENT = 0.95; //percent of Msec to gradually ramp arm pwr



///////////////GLOBAL VARIABLES////////////////
//Gyro variables
float currentValue = 0.0; //current value of adjusted gyro reading (w/o BIAS)
float angleChange = 0.0; //amt of change in angle turned
float timeChange = 0.0; //amt of change in time (sec)
float gCurrTotalMove = 0.0; //amt turned already
float sCurrTotalTurn = 0.0; //amt of turn in moveStraight
float remainingTurn = DEFAULT_VAL; //amt of turn remaining
float error = 0.0;
float gyroReading = 0.0; //gyro reading WHAT IS THIS VARIABLE FOR
float adjustedTarget = 0.0; //adjusted amt of turn remaining
int IRVal = 0;

//Encoder stop ramming variables
float leftEncoderPrev = 0.0;
float rightEncoderPrev = 0.0;
float leftEncoderCurr = 0.0;
float rightEncoderCurr = 0.0;
float leftEncoderDiff = 0.0;
float rightEncoderDiff = 0.0;
float leftEncoderRate = 0.0;
float rightEncoderRate = 0.0;
float leftEncoderError = 0.0;
float rightEncoderError = 0.0;
const float CHANGE_AVG_RATE = 42.0; //magic num
const float THRESHOLD = 5.0; //magic num
const float TIME_INTERVAL = 100.0; //magic numish


#endif;
