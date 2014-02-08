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


bool getTap(int joy, int btn)
{
	if(joy1Btn(btn) && joy == 1)
	{
		ClearTimer(T4);
		//-/writeDebugStreamLine("joy1 pressed");

		while(time1[T4] < TAP_THRESH)
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
		ClearTimer(T4);
		//-/writeDebugStreamLine("pressed");
		while(time1[T4] < TAP_THRESH)
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


//////////////GENERAL TASKS///////////////
/************HANG*************
FAILSAFE ACTIVE
Hold down btn 7: Winch forward
Hold down btn 4: Winch backward, Open servo
Hold down btn 1: Activate hangman
*****************************/
task Hang()
{
	bool winchForward = false;
	bool winchBackward = false;
	bool hangmanOn = false;

	while(true)
	{
		getJoystickSettings(joystick);
		//Check conditions
		if(FSon)
		{
			winchForward = bothBtn(7);
			winchBackward = bothBtn(4);
			hangmanOn = bothBtn(1);
		}
		else
		{
			winchForward = anyBtn(7);
			winchBackward = anyBtn(4);
			hangmanOn = anyBtn(1);
		}


		//Hangman movement
		if(hangmanOn)
		{
			//-/writeDebugStreamLine("hangman mot 90");
			motor[hangmanMot] = HANGMAN_UP;
		}
		else
		{
			motor[hangmanMot] = STOP;
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
			motor[winchMot] = WINCH_R;
			servo[antiRatchet] = AR_OPEN; //open
		}
		else
		{
			motor[winchMot] = STOP;
			servo[antiRatchet] = AR_CLOSED; //closed
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
*****************************/
task JoyControl()
{
	while(true)
	{
		getJoystickSettings(joystick);

		if(getTap(1,9))
		{
			DTjoy1 = !DTjoy1;
			/*//-/PlayTone(300,1);
			if(DTjoy1)
				writeDebugStreamLine("Joy 1: DT on");
			else
				writeDebugStreamLine("Joy 1: ANI on");*/
		}

		if(getTap(2,9))
		{
			ANIjoy2 = !ANIjoy2;
			/*//-/PlayTone(500,1);
			//-/if(ANIjoy2)
				writeDebugStreamLine("Joy 2: ANI on");
			else
				writeDebugStreamLine("Joy 2: DT on");*/
		}

		if(getTap(0,10))
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
