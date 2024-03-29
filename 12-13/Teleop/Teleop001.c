#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S2,     HTSMUX,         sensorI2CCustom)
#pragma config(Motor,  motorB,          flagLeft,      tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          flagRight,     tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     driveRight,    tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     driveLeft,     tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     armRight,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     armLeft,       tmotorTetrix, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                           Tele-Operation Mode Code Template
//
// This file contains a template for simplified creation of an tele-op program for an FTC
// competition.
//
// You need to customize two functions with code unique to your specific robot.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

//#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.
#include "teleppppoooo.c"
#include "common.h"
#include "hitechnic-sensormux.h"
#include "lego-touch.h"
const tMUXSensor LEGOTOUCH = msensor_S2_4;

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                    initializeRobot
//
// Prior to the start of tele-op mode, you may want to perform some initialization on your robot
// and the variables within your program.
//
// In most cases, you may not have to add any code to this function and it will remain "empty".
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

void initializeRobot()
{
  return;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                         Main Task
//
// The following is the main code for the tele-op robot operation. Customize as appropriate for
// your specific robot.
//
// Game controller / joystick information is sent periodically (about every 50 milliseconds) from
// the FMS (Field Management System) to the robot. Most tele-op programs will follow the following
// logic:
//   1. Loop forever repeating the following actions:
//   2. Get the latest game controller / joystick settings that have been received from the PC.
//   3. Perform appropriate actions based on the joystick + buttons settings. This is usually a
//      simple action:
//      *  Joystick values are usually directly translated into power levels for a motor or
//         position of a servo.
//      *  Buttons are usually used to start/stop a motor or cause a servo to move to a specific
//         position.
//   4. Repeat the loop.
//
// Your program needs to continuously loop because you need to continuously respond to changes in
// the game controller settings.
//
// At the end of the tele-op period, the FMS will autonmatically abort (stop) execution of the program.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////


int driveLeftPwr = 0;
int driveRightPwr = 0;
task main()
{
  initializeRobot();

  waitForStart();   // wait for start of tele-op phase
	StartTask(Arm);
	StartTask(weightedRing);
  while (true)
  {
	  getJoystickSettings(joystick);


	  if (joy1Btn(5) == true)
    {
    	if(abs(joystick.joy1_y1) > 10)
      	driveLeftPwr= joystick.joy1_y1/3;
     	else
     		driveLeftPwr = 0;
     	if(abs(joystick.joy1_y2) > 10)
      	driveRightPwr=joystick.joy1_y2/3;
     	else
     		driveRightPwr = 0;
    }

    //Normal drive speed
    else
    {
    	if(abs(joystick.joy1_y1) > 10)
      	driveLeftPwr= joystick.joy1_y1;
     	else
     		driveLeftPwr = 0;
     	if(abs(joystick.joy1_y2) > 10)
      	driveRightPwr=joystick.joy1_y2;
     	else
     		driveRightPwr = 0;
    }
    motor[driveLeft]=driveLeftPwr;
    motor[driveRight]=driveRightPwr;

  }
}
