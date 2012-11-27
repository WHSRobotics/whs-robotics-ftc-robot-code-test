#ifndef AUTONOMOUS_CONSTANTS_GLOBVARS.H;
#define AUTONOMOUS_CONSTANTS_GLOBVARS.H;

///////////////////KONSTANTS///////////////////

const float LOW_TURK = 0.75; //turn konstant for low power
const float MID_TURK = 0.9; //turn konstant for mid power
const float HIGH_TURK = 1.0; //turn konstant for high power
const float ADJUST_M = 1.0; //slope of linear equation to scale target angle
const float ADJUST_B = 7.0; //y-intercept of linear equation to scale target angle

const float MILLISECOND = 1000.0; //number of milliseconds in one second
const float DEFAULT_VAL = 42.0; //generic value for initialization that's greater than 0


///////////////GLOBAL VARIABLES////////////////

float currentValue = 0.0;
float angleChange = 0.0;
float timeChange = 0.0;
float currTotalMove = 0.0;
float remainingTurn = DEFAULT_VAL;
float error = 0.0;
float gyroReading = 0.0;
float adjustedTarget = 0.0;

#endif;
