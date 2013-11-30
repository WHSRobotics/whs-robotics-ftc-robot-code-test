#ifndef TELEOP_GLOBVARS1.H;
#define TELEOP_GLOBVARS1.H;

//---------INCLUDES------------
#include "JoystickDriver.c";

//----------CONFIGURATION----------
/*
1 motor controller - drive train
  + MotorD = leftDrive (encoder)
  + MotorE = rightDrive (encoder)
1 motor controller - scoring arm
  + MotorF = leftArm
  + MotorG = rightArm
1 motor controller - hang lift
	+ MotorH = hang1
	+ MotorI = hang2
1 servo controller - hang arm and box drop
  + servo4 - intakeServo
  + servo5 - hangServo1
  + servo6 - hangServo2
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
