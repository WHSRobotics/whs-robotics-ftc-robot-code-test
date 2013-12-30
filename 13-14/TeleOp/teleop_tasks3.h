#ifndef TELEOP_TASKS3.H;
#define TELEOP_TASKS3.H;

//joystick1 - drive train
//joystick2 - arm & intake

////////////INCLUDE/////////////
#include "teleop_globVars1.h";



/////////////FUNCTIONS//////////////
/*Initialization*/
void InitializeRobot()
{
        //ready KONSTANTS
        const int FLAG_READY = 120;
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

////LOW PRIORITIZATION FUNCTIONS/////
/* Prioritization functions allow one
** driver to override the other based
** set prioritization controls. Each
** function is associated with a task. */

void joy1Arm()
{
        while(true)
        {
                //-----------joystick 1------------//
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
                else //if not pressed/pressed at same time
                {
                        runArm(STOP);
                }
        }
}

///////////////TASKS////////////////

///////////////////////////////////////////
//////-------------ARM--------------///////
// Button presses drive motors at set speeds.
// USED: Btn 6 (up), 8 (down)
///////////////////////////////////////////
task Arm()
{
        while(true)
        {
                //-----------joystick 2------------//
                //high priority
                getJoystickSettings(joystick);
                if(joy2Btn(6) && !joy2Btn(8)) //move arm up
                {
                        runArm(80);
                }
                else if(joy2Btn(8) && !joy2Btn(6)) //move arm down
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


///////////////////////////////////////////
//////---------DRIVE TRAIN----------///////
// Direct tank drive to motors.
// USED: joysticks (speed and direction)
///////////////////////////////////////////
task DriveTrain()
{
        //Drive Train KONSTANTS
        const int HI_THRESH = 25; 				//high joy threshold
        const int LOW_THRESH = 15; 				//low joy threshold
        const float JOY_SCALE = 25.0/32.0; //scale from joystick val to motor power
				const int THRESHOLD = 10; 				//the minimum number to make the joystick move
        short leftPow1 = 0;								//the value for the left drive on joystick 1
        short rightPow1 = 0;							//the value for the right drive on joystick 1
        short leftPow2 = 0;								//the value for the left drive on joystick 2
        short rightPow2 = 0;							//the value for the right drive on joystick 2

        while(true)
        {
        				// get new values for the joysticks
                getJoystickSettings(joystick);

                //to scale the joystick values from -100 to 100
                leftPow1 = (int)((float)joystick.joy1_y1) * JOY_SCALE;
                rightPow1 = (int)((float)joystick.joy1_y2) * JOY_SCALE;
                leftPow2 = (int)((float)joystick.joy2_y1) * JOY_SCALE;
                rightPow2 = (int)((float)joystick.joy2_y2) * JOY_SCALE;

                //Prioritizing joystick 1 over joystick 2
                //and ensure the robot doesn't accidently move with small values of the joystick
                if ( (abs(leftPow1) > THRESHOLD) || (abs(rightPow1) > THRESHOLD) )
                {
                	//-----------joystick 1------------//
                	motor[leftDrive] = leftPow1;
                	motor[rightDrive] = rightPow1;
                }
                else if ((abs(leftPow2) > THRESHOLD) || (abs(rightPow2) > THRESHOLD))
                {
                	//-----------joystick 2------------//
                	//if you don't use joystick 1, joystick 2 can move the robot
                	motor[leftDrive] = leftPow2;
                	motor[rightDrive] = rightPow2;
                }
                else
                {
                	//to stop the robot from moving
                	motor[leftDrive] = 0;
                	motor[rightDrive] = 0;
                }
        }
}


///////////////////////////////////////////
//////-------------HANG-------------///////
// Button presses drive motors at set speeds.
// USED: Btn 1 (FS, Raise)
///////////////////////////////////////////
task Hang()
{
        //Hang Servo Positions
        const int POS_ONE = 60;
        const int END_ONE = 250;
        const int POS_TWO = 180;
        const int END_TWO = 0;

        while(true)
        {
                getJoystickSettings(joystick);
                //Activates winch lift motors
                if(joy1Btn(7) && joy2Btn(7))
                {
                        motor[hang1] = MOT_MAX;
                        motor[hang2] = MOT_MAX;
                }
                else
                {
                        motor[hang1] = STOP;
                        motor[hang2] = STOP;
                }
                //Only when the button for the lift arms are pressed, lift
                if(joy1Btn(1) && joy2Btn(1))
                {
                        servoTarget[hangServo1] = END_ONE;
                        servoTarget[hangServo2] = END_TWO;
                }
                //Otherwise, Drop the servo arms
                else
                {
                        servoTarget[hangServo1] = POS_ONE;
                        servoTarget[hangServo2] = POS_TWO;
                }
        }
}


///////////////////////////////////////////
//////------------INTAKE------------///////
// Button presses drive motors at set speeds.
// USED: Btn 5 (eat/drop), Btn 2 (Toggle Intake)
///////////////////////////////////////////
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


///////////////////////////////////////////
//////------------INTAKE------------///////
// Button presses drive motors at set speeds.
// USED: Btn 5 (eat/drop), Btn 2 (Toggle Intake)
///////////////////////////////////////////
/*task Flag()
{
        ///////Flag Stages///////
        const int STG_READY = 0;
        const int STG_SET = 1;
        const int STG_GO = 2;
        ///////Flag Positions///////
        const int POS_READY = 100;
        const int POS_SET = 50;
        const int POS_GO = 0;

        int currStage = STG_READY;
        while(true)
        {
                getJoystickSettings(joystick);

                if(currStage == STG_READY)
                {
                        if(joy1Btn(4) && joy2Btn(4))
                        {
                                servo[flagServo] = POS_SET;
                                currStage = STG_SET;
                        }
                        else
                        {
                                servo[flagServo] = POS_READY;
                        }
                }
                else if(currStage == STG_SET)
                {
                        if(joy1Btn(3) && joy2Btn(3))
                        {
                                servo[flagServo] = POS_GO;
                                currStage = STG_GO;
                        }
                        else
                        {
                                servo[flagServo] = POS_SET;
                        }
                }
                else
                {
                        servo[flagServo] = POS_GO;
                }
        }
}*/



#endif;
