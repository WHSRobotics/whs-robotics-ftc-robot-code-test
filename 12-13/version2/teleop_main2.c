#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     driveRight,    tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     driveLeft,     tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     armRight,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     armLeft,       tmotorTetrix, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//INSERT PRAGMAS

/*************************************
** This is version 2 of teleop main **
** for WHS Robotics FTC Team 542,   **
** for Ring It Up ('12-'13).        **
**************************************/

//-----------------------Includes-------------------------
#include "teleop_tasks2.h";


/*********************************
** initializeRobot initializes  **
** servos to starting positions **
** and finds error for sensors. **
**********************************/
void initializeRobot()
{
  return;
}


//-------------------------main---------------------------
task main()
{
  initializeRobot();

  waitForStart();

  //start tasks
  StartTask(RunTankDrive);
  StartTask(RunArm);

  while(true) //teleop phase
  {
    getJoystickSettings(joystick);

    //Sensor-related thing joy1Btn(1)
    //Sensor-related thing joy1Btn(2)
    //Sensor-related thing joy1Brn(3)

  }
}
