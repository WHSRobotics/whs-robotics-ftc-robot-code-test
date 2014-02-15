#ifndef AUTO_GLOBVARS_SWEDR.H;
#define AUTO_GLOBVARS_SWEDR.H;

/**********************************
** WHS Robotics  |  FTC Team 542 **
** Block Party! 2013-2014 Season **
** Autonomous Version 4          **
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
const int INTAKE_R = -50;
const int MAX = 100;

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
//Conversions
const float JOY_MAP = 0.78125;
const float SERVO_MAP_DEG = 255.0/180.0;
const float SERVO_MAP = 255.0/PI;
const float RAD_DEG = 180.0/PI;

const int FL_POS1 = 0;
const int FL_POS2 = 230;//232;//214;

const int FR_POS1 = 30;//24;
const int FR_POS2 = 233;//210;

const int BL_POS1 = 34;//30;
const int BL_POS2 = 255;//240;

const int BR_POS1 = 30;//10;//30;
const int BR_POS2 = 251;//234;//228;

const float FL_SERVO_MAP = (FL_POS2 - FL_POS1)/180.0;
const float FR_SERVO_MAP = (FR_POS2 - FR_POS1)/180.0;
const float BL_SERVO_MAP = (BL_POS2 - BL_POS1)/180.0;
const float BR_SERVO_MAP = (BR_POS2 - BR_POS1)/180.0;

const float INCH_ENCODERVALUE = 158.057322; //number of encoder values in one inch forward for a 4 inch wheel
											//(number of encoder values in one rotation[1440])/(wheel diameter[2.9]*pi[3.14...])
//Measures
const float HALF_WIDTH_X = 6.8125;
const float HALF_LENGTH_Y = 7.125;

const float PWR_ADJUST = 7.355;//3.9 //7.5

////Arm KONSTANTS////
//moveArm
const float MAJOR_MSEC_PERCENT = 0.05; //percent of Msec to run arm at full pwr
const float MINOR_MSEC_PERCENT = 0.95; //percent of Msec to gradually ramp arm pwr

////Box KONSTANTS////
const int BOX_OPEN = 175;
const int BOX_CLOSED = 255;


///////////////GLOBAL VARIABLES////////////////
//Concurrent variables
int currIR = 0;

//Gyro variables
float currentValue = 0.0; //current value of adjusted gyro reading (w/o BIAS)
float angleChange = 0.0; //amt of change in angle turned
float timeChange = 0.0; //amt of change in time (sec)
float gCurrTotalMove = 0.0; //amt turned already
float sCurrTotalTurn = 0.0; //amt of turn in moveStraight
float remainingTurn = DEFAULT_VAL; //amt of turn remaining
float error = 0.0;
float adjustedTarget = 0.0; //adjusted amt of turn remaining


int tally[4]; //declare vars for tallies for each position
const int thresh[4] = {0,0,0,0}; //declare vars for thresholds for each position


#endif;
