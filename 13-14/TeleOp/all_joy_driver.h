#ifndef ALL_JOY_DRIVER.H;
#define ALL_JOY_DRIVER.H;

/*
winch = dc motor
flag = dc motor
velcro = nxt motor
intake = 2 nxt motors
turntable = dc motor
ratchetDisable = servo
*/


#include "JoystickDriver.c"
#include "teleop_globVars4-sw.h"


/////////////GENERAL FUNCTIONS/////////////
bool anyBtn(int btn)
{
	return (joy1Btn(btn) || joy2Btn(btn));
}


bool getTap(int joy, int btn, TTimers timer)
{
	if(joy1Btn(btn) && joy == 1)
	{
		ClearTimer(timer);
		//-/writeDebugStreamLine("joy1 pressed");

		while(time1[timer] < TAP_THRESH)
		{
			if(!joy1Btn(btn))
			{
				//-/writeDebugStreamLine("joy1 tapped");
				return true;
			}
		}
		//-/writeDebugStreamLine("joy1 abort");
		return false;
	}
	else if(joy2Btn(btn) && joy == 2)
	{
		ClearTimer(T4);
		//-/writeDebugStreamLine("joy2 pressed");
		while(time1[T4] < TAP_THRESH)
		{
			if(!joy2Btn(btn))
			{
				//-/writeDebugStreamLine("joy2 tapped");
				return true;
			}
		}
		//-/writeDebugStreamLine("joy2 abort");
		return false;
	}
	else if(anyBtn(btn) && joy == 0) //any joystick
	{
		ClearTimer(timer);
		//-/writeDebugStreamLine("pressed");
		while(time1[timer] < TAP_THRESH)
		{
			if(!anyBtn(btn))
			{
				//-/writeDebugStreamLine("tapped");
				return true;
			}
		}
		//-/writeDebugStreamLine("abort");
		return false;
	}
	else
	{
		return false;
	}
}


bool bothBtn(int btn)
{
	return (joy1Btn(btn) && joy2Btn(btn));
}


bool getTopHat(int joy, int btn)
{
	if(joy == 1)
		return (joystick.joy1_TopHat == btn);
	else if(joy == 2)
		return (joystick.joy2_TopHat == btn);
	else
		return false;
}



////////////////ANI CONTROLS////////////////
void runIntake(float motPow)
{
	motor[intakeL] = motPow;
	motor[intakeR] = motPow;
}

void runArm(float motPow)
{
	motor[armL] = motPow;
	motor[armR] = motPow;
}



/////////////////DT CONTROLS//////////////////
//-CONSISTENCY-Swivel Direction aligns all swivel servos to the same angle
void swivelDirection(float angle)
{
	servo[swiFL] = angle;
	servo[swiBL] = angle;
	servo[swiFR] = angle;
	servo[swiBR] = angle;
}


//-CONSISTENCY-Assigns same motor power to all motors
void runPow(float motPow)
{
	motor[swiFL] = motPow;
	motor[swiBL] = motPow;
	motor[swiFR] = motPow;
	motor[swiBR] = motPow;
}



//////////////GENERAL TASKS///////////////
/************WINCH*************
FAILSAFE ACTIVE
Hold down btn 7: Winch forward
Hold down btn 4: Winch backward, Open servo
*****************************/
task Winch()
{
	bool winchForward = false;
	bool winchBackward = false;

	while(true)
	{
		getJoystickSettings(joystick);
		//Check conditions
		if(FSon)
		{
			winchForward = bothBtn(7);
			winchBackward = bothBtn(4);
			//hangmanOn = bothBtn(1);
		}
		else
		{
			winchForward = anyBtn(7);
			winchBackward = anyBtn(4);
			//hangmanOn = anyBtn(1);
		}

		//Winch & Anti-ratchet movement
		if(winchForward && !winchBackward)
		{
			//-/writeDebugStreamLine("winch forward");
			motor[winchMot] = MAX;
		}
		else if(winchBackward)
		{
			//-/writeDebugStreamLine("winch backward");

			servo[antiRatchet] = AR_OPEN; //open
			wait1Msec(800);
			motor[winchMot] = WINCH_R;
		}
		else
		{
			motor[winchMot] = STOP;
			wait1Msec(800);
			servo[antiRatchet] = AR_CLOSED; //closed
		}
	}
}


/************HANG*************
Tap btn 1: Activate hangman sequence
*****************************/
task Hangman()
{
	//bool hangmanOn = false;

	while(true)
	{
		getJoystickSettings(joystick);
		//Check conditions
		/*if(joy2Btn(1))
			hangmanOn = true;*/

		//Hangman movement
		if((joy2Btn(1) && ANIjoy2) || (joy1Btn(1) && !DTjoy1) || (!ANIjoy2 && DTjoy1 && (joy1Btn(1) || joy2Btn(1))))//hangmanOn)
		{
			//-/writeDebugStreamLine("hangman mot 90");
			intakeOn = false;
			motor[hangmanMot] = HANGMAN_UP;
		}
		else
		{
			wait1Msec(200);
			intakeOn = true;
			motor[hangmanMot] = HANGMAN_DOWN;
		}
	}
}


/************FLAG*************
FAILSAFE ACTIVE
Btn 3 simultaneously pressed on
both joysticks runs a
DC Motor at +100 power.
*****************************/
task Flag()
{
	bool flagOn = false;
	while(true)
	{
		getJoystickSettings(joystick);
		//Check conditions
		if(FSon)
			flagOn = bothBtn(3);
		else
			flagOn = anyBtn(3);

		if(flagOn)
		{
			writeDebugStreamLine("Flag 100");
			motor[flagMot] = MAX;
		}
		else
		{
			motor[flagMot] = STOP;
		}
	}
}



/********JOY CONTROL*********
Btn 9: Switch between control schemes
Btn 10: Disable Failsafe
Use for emergency situations
Timer 4
*****************************/
task JoyControl()
{
	while(true)
	{
		getJoystickSettings(joystick);

		if(getTap(1,9, T4))
		{
			DTjoy1 = !DTjoy1;
			/*//-/PlayTone(300,1);
			if(DTjoy1)
				writeDebugStreamLine("Joy 1: DT on");
			else
				writeDebugStreamLine("Joy 1: ANI on");*/
		}

		if(getTap(2,9, T4))
		{
			ANIjoy2 = !ANIjoy2;
			/*//-/PlayTone(500,1);
			//-/if(ANIjoy2)
				writeDebugStreamLine("Joy 2: ANI on");
			else
				writeDebugStreamLine("Joy 2: DT on");*/
		}

		if(getTap(0,10, T4))
		{
			FSon = false;
		}
	}
}


/**********************
//TANK DRIVE CODE HERE
***********************/
/*task TankDrive()
{
	while(true)
	{
		getJoystickSetting(joystick);

	}
}*/


#endif;
