#ifndef TELEOP_GLOBVARS1.H;
#define TELEOP_GLOBVARS1.H;

//---------INCLUDES------------
#include "JoystickDriver.c";

//----------CONFIGURATION----------
/*
1 motor controller - drive train
  + MotorD = leftDrive (encoder)
  + MotorE = rightDrive (encoder)
1 motor controller - lift and the turntable
  + MotorF = hangMotor
  + MotorG = tableMotor (encoder)
1 servo controller - arm
  + servo1 - armServo (assuming that only 1 servo is being used for the arm)
2 direct NXT motors - intake
  + motorA = leftIntake
  + motorB = rightIntake
*/


//-----------KONSTANTS----------
////////General KONSTANTS////////
const int STOP = 0;
const int MOT_MAX = 100;

///////Power KONSTANTS////////
//const int TABLE_HI_POW = 50;
//const int TABLE_LOW_POW = 30;
const int INTAKE_POW = 100;

///////Threshold KONSTANTS///////
const int DRIVE_HI_THRESH = 25;
const int DRIVE_LOW_THRESH = 15;



#endif;
