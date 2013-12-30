#ifndef TELEOP_GLOBVARS2.H;
#define TELEOP_GLOBVARS2.H;

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

/*
//-----------KONSTANTS----------
////////General KONSTANTS////////
const int STOP = 0;
const int MOT_MAX = 100;

///////Power KONSTANTS////////
const int INTAKE_POW = 100;

///////Threshold KONSTANTS///////
const int DRIVE_HI_THRESH = 25;
const int DRIVE_LOW_THRESH = 15;

//////Servo Position KONSTANTS//////
///Hang
const int HANG_POS_ONE = 60;
const int HANG_END_ONE = 250;
const int HANG_POS_TWO = 180;
const int HANG_END_TWO = 0;
///Flag
const int FLAG_POS_READY = 120;
const int FLAG_POS_SET = 50;
const int FLAG_POS_GO = 0;

///////Flag Stages///////
const int FLAG_STG_READY = 0;
const int FLAG_STG_SET = 1;
const int FLAG_STG_GO = 2;*/


#endif;
