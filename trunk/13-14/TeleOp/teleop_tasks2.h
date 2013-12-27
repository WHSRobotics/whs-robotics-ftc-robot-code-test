#ifndef TELEOP_TASKS2.H;
#define TELEOP_TASKS2.H;

//joystick1 - drive train
//joystick2 - arm & intake

///////////INCLUDE///////////
#include "teleop_globVars1.h";



///////////FUNCTIONS//////////
/*Initialization*/
void InitializeRobot()
{
//ready KONSTANTS
const int FLAG_READY = 125;
const int AUTO_INIT = 15;
const int LEFT_HANG_INIT = 60;
const int RIGHT_HANG_INIT = 180;

//set to ready positions
servo[flagServo] = FLAG_READY;
servo[autoServo] = AUTO_INIT;
servo[hangServo1] = LEFT_HANG_INIT;
servo[hangServo2] = RIGHT_HANG_INIT;
return;
}

/* Groups intake motors together
** to run the same power to them
** at the same time. */
void runIntake(int power)
{
motor[leftIntake] = power;
motor[rightIntake] = power;
}

/* Groups arm motors together
** to run the same power to them
** at the same time. */
void runArm(int power)
{
motor[leftArm] = power;
motor[rightArm] = power;
}

///LLOW PRIORITIZATION FUNTIONS/////
/* Prioritization functions allow one
** driver to override the other based
** ser prioritization controls. Each
** function is associated with a task. */

void joy1Arm()
{
while(true)
{
//--------joystick 1------------//
//low priority
getJoystickSettings(joystick);
if(joy1Btn(6) && !joy1Btn(8)) //move arm up
{
runArm(80);
}
else if(joy1Btn(8) && !joy1Btn(6)) //move arm down
{
runArm(-40);
}
else // if not pressed/pressed at same time
{
runArm(STOP);
}
}
}

void joy2drive()
{
//---------joystick 2------------//
//low priority
//higher thresolds than joy1
getJoystickSettings(joystick);
motor[leftDrive] = abs(joystick.joy2_y1 * 25/32) > DRIVE_HI_THRESH
? joystick.joy2_y1 * 25/32 // if left movement is significant
: STOP; //if left movement is insignificant
motor[rightDrive] = abs(joystick.joy2_y2 *25/32) > DRIVE_HI_THRESH
? joystick.joy2_y2 * 25/32 //if right movement is significant
: STOP; //if right movement is insignificant
}

//////////TASKS//////////

///////////////////////////////////////////////
/////////-------------ARM---------------///////
// BUtton presses drive motors at set speeds.
// USED: Btn 6 (up), 8 (down)
////////////////////////////////////////////
task Arm()
{
while(true)
{
//-----------joystick 2----------------//
//hight priority
getJoystickSettings(joystick);
if(joy2Btn(6) && !joy2Btn(8)) // move arm up
{
runArm(80);
}
else if(joy2Btn(8) && !joy2Btn(6)) // move arm down
{
runArm(-40);
}
else //if not pressed/pressed at same time
{
//joy1Arm();
runArm(STOP);
}
}
}

/////////////////////////////////////////////
////////--------DRIVE TRAIN---------/////////
// Direct tank drive to motors.
// USED: joystick (speed and direction)
/////////////////////////////////////////
task DriveTrain()
{
//Drive Train KONSTANTS
const int HI_THRESH = 25; //high joy threshold
const int LOW_THRESH = 15; //low joy threshold
const int JOY_SCALE = 25/32; //scale from joystick val to motor power
int leftPow = 0;
int rightPow = 0;

while(true)
{
//high priority
//-----------joystick 1----------//
getJoystickSettings(joystick);

leftPow = joystick.joy1_y1 * JOY_SCALE;
rightPow = joystick.joy1_y2 * JOY_SCALE;

if(abs(leftPow) > LOW_THRESH || abs(rightPow) > LOW_THRESH)
//if movement is significant
{
motor[leftDrive] = joystick.joy1_y1 * JOY_SCALE;
motor[rightDrive] = joystick.joy1_y2 * JOY_SCALE;
}
else //if movement is insignificant
{
joy2drive();
}
}
}

//////////////////////////////////
////----------Intake----------////
// Button presses drive motoros at set speeds.
// USED: Btn 5 (east/drop), Btn 2 (Toggle Intake)
//////////////////////////////////
task Intake()
{
bool toggle = true;
while(true)
{
getJoystickSettings(joystick);
//Activates Servo Drop and Returns Servo to Initial Position
servoTarget[intakeServo] = joy2Btn(5)
? 150
: 80;
if(joy2Btn(2))
{
toggle = !toggle;
wait10Msec(25);
}
if(toggle)
{
runIntake(INTAKE_POW);
}
else
{
	runIntake(STOP);
}
}
}

#endif;
