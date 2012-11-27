#ifndef AUTONOMOUS_CONSTANTS_GLOBVARS.H;
#define AUTONOMOUS_CONSTANTS_GLOBVARS.H;

///////////////////KONSTANTS///////////////////

const float LOW_TURK = 0.75;
const float MID_TURK = 0.9;
const float HIGH_TURK = 1.0;
const float ADJUST_M = 1.0;
const float ADJUST_B = 7.0;

///////////////GLOBAL VARIABLES////////////////

float currentValue = 0.0;
float angleChange = 0.0;
float timeChange = 0.0;
float currTotalMove = 0.0;
float remainingTurn = 42.0;
float error = 0.0;
float gyroReading = 0.0;
float adjustedTarget = 0.0;

#endif;
