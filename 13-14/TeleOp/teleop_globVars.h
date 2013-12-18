#ifndef TELEOP_GLOBVARS1.H;
#define TELEOP_GLOBVARS1.H;

#include "JoystickDriver.c";

const int STOP = 0;
const int MOT_MAX = 100;

const int INTAKE_POW = 100;
const int DRIVE_HI_THRESH = 25;
const int DRIVE_LOW_THRESH = 15;
const int HANG_POS_ONE = 60;
const int HANG_END_ONE = 250;
const int HANG_POS_TWO = 180;
const int HANG_END_TWO = 0;

const int FLAG_POS_READY = 120;
const int FLAG_POS_SET = 50;
const int FLAG_END_TWO = 0;

const int FLAG_STG_READY = 0;
const int FLAG_STG_SET = 1;
const int FLAG_STG_GO = 2;
#endif;
