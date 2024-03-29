#ifndef AUTO_GLOBVARS.H;
#define AUTO_GLOBVARS.H;

/**********************************
** WHS Robotics  |  FTC Team 542 **
** Block Party! 2013-2014 Season **
** Autonomous Version 1          **
** Global Variables              **
***********************************/



///////////////////////////INCLUDES////////////////////////////
//#include "hitechnic-sensormux.h"  //header file for SMUX
#include "hitechnic-irseeker-v2.h" //header file for IR seeker v2! :D
#include "hitechnic-gyro.h" //driver for gyro
//#include "hitechnic-touchmux.h"  //header file for TUX
#include "JoystickDriver.c"

///////////////////KONSTANTS///////////////////
////General KONSTANTS////
const float MILLISECOND = 1000.0; //number of milliseconds in one second
const float DEFAULT_VAL = 42.0; //generic value for initialization that's greater than 0
const float STOP = 0.0;

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
float adjustedTarget = 0.0; //adjusted amt of turn remaining
int currIR = 0;

int tally[4]; //declare vars for tallies for each position
const int thresh[4] = {0,0,0,0}; //declare vars for thresholds for each position


#endif;
