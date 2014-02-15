#ifndef TELEOP_GLOBVARS4-SW.H;
#define TELEOP_GLOBVARS4-SW.H;

////////////GLOBAL VARS//////////////
//////NOTE: getTap uses Timer T4
//Control scheme variables
bool DTjoy1 = true;
bool ANIjoy2 = true;
bool FSon = true;
//Intake variables
bool intakeOn = true;
//bool intakeReversed = false;
//bool boxOpen = false;

//Drive Control variables
bool tankDrive = true;


/////////////KONSTANTS/////////////
//Power KONSTANTS
const int STOP = 0;
const int MAX = 100; //intake forward, winch forward, flag on
const int ARM_UP = 90;
const int ARM_DOWN = -50;
//const int INTAKE_R = -50;
const int HANGMAN_UP = 90;
const int HANGMAN_DOWN = -50;
const int WINCH_R = -100;
const int AR_OPEN = 40; //anti-ratchet open
const int AR_CLOSED = 255; //anti-ratchet closed
const int BOX_OPEN = 150;//175;
const int BOX_CLOSED = 255;

//THRESHOLDS
const int TAP_THRESH = 1000; //1000 Msec timeout

//Drive Train KONSTANTS
const int HI_THRESH = 25;
const int LOW_THRESH = 15;
const int IDLE_THRESH = 10;
const float HALF_WIDTH_X = 6.8125;
const float HALF_LENGTH_Y = 7.125;
const float JOY_MAP = 0.78125;
const float SERVO_MAP = 255.0/PI;//255.0/PI; //radian to servo val
const float OROT_SCALE_DIV = sqrt(2.0 * HALF_WIDTH_X * HALF_LENGTH_Y);
const float ROT_SCALE = 25.0/128/OROT_SCALE_DIV;
const float TANK_SPEED_SCALE = 1.0;
const float SWERVE_SPEED_SCALE = 0.585937;

const int FL_POS1 = 0;
const int FL_POS2 = 230;//232;//214;
const int FR_POS1 = 30;//24;
const int FR_POS2 = 233;//210;

const int BL_POS1 = 34;//30;
const int BL_POS2 = 255;//240;

const int BR_POS1 = 30;//10;//30;
const int BR_POS2 = 251;//234;//228;

const float FL_SERVO_MAP = (FL_POS2 - FL_POS1)/PI;
const float FR_SERVO_MAP = (FR_POS2 - FR_POS1)/PI;
const float BL_SERVO_MAP = (BL_POS2 - BL_POS1)/PI;
const float BR_SERVO_MAP = (BR_POS2 - BR_POS1)/PI;


#endif;
