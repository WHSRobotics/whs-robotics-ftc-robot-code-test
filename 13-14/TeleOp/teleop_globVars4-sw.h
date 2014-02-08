#ifndef TELEOP_GLOBVARS4-SW.H;
#define TELEOP_GLOBVARS4-SW.H;

////////////GLOBAL VARS//////////////
//////NOTE: getTap uses Timer T4
//Control scheme variables
bool DTjoy1 = true;
bool ANIjoy2 = true;
bool FSon = true;
//Intake variables
bool intakeOn = false;
bool intakeReversed = false;
bool boxOpen = false;
//Drive Control variables
bool tankDrive = false;


/////////////KONSTANTS/////////////
//Power KONSTANTS
const int STOP = 0;
const int MAX = 100; //intake forward, winch forward, flag on
const int ARM_UP = 90;
const int ARM_DOWN = -50;
const int INTAKE_R = -50;
const int HANGMAN_UP = 90;
const int WINCH_R = -100;
const int AR_OPEN = 255; //anti-ratchet open
const int AR_CLOSED = 90; //anti-ratchet closed

//THRESHOLDS
const int TAP_THRESH = 1000; //1000 Msec timeout

//Drive Train KONSTANTS
const int HI_THRESH = 25;
const int LOW_THRESH = 15;
const int IDLE_THRESH = 10;
const float JOY_MAP = 0.78125;
const float SERVO_MAP = 255.0/PI;
const float ROT_ONLY_SCALE = 0.075;
const float ROT_SCALE = 0.025;
const float TANK_SPEED_SCALE = 1.0;
const float SWERVE_SPEED_SCALE = 1.0;
const float HALF_WIDTH_X = 6.8125;
const float HALF_LENGTH_Y = 7.125;


#endif;
