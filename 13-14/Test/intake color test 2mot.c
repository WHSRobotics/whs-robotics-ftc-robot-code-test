#pragma config(Hubs,  S1, HTMotor,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     colorSensor,    sensorCOLORFULL)
#pragma config(Motor,  mtr_S1_C1_1,     intakeMot1,    tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     intakeMot2,    tmotorTetrix, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//#include "JoystickDriver.c";

bool intakeOn = false;
	string object = "";
	int numBlock = 0;

task Intake()
{
	bool intakeOn = true;
	bool isBlock = false;

	motor[intakeMot1] = 80;//60//50//43//35
	motor[intakeMot2] = -80;

	//Black, Blue, Green, Yellow, Red, White
	while(numBlock < 4)
	{
		if(SensorValue[colorSensor] > 1) //Greater than Blue
		{
			wait1Msec(75);
			if(SensorValue[colorSensor] > 1) //Greater than Blue
			{
				PlayTone(440,1);
				object = "block ";
				isBlock = true;
			}
			else
			{
			}
		}

		else
		{
			object = "      ";
			if(isBlock)
			{
				numBlock++;
				isBlock = false;
			}
		}

			nxtDisplayString(3,"%s",object);
		nxtDisplayString(4,"numBlock: %d", numBlock);
		nxtDisplayString(5,"%d",SensorValue[colorSensor]);
	}
		/*wait1Msec(1750);//1250//2000higher angle: higher time
		motor[intakeMot] = 0;
		wait1Msec(1000);
		motor[intakeMot] = -80;
		wait1Msec(1500);
		motor[intakeMot] = 0;*/


		intakeOn = false;
}
task main()
{
	StartTask(Intake);
	while(true)
	{

	}
	/*while(true)
	{
		getJoystickSettings(joystick);
		if(Joy1Btn(6) && !Joy1Btn(8))
		{
			if(!intakeOn)
			{
				StartTask(Intake);
			}
		}
		else if(Joy1Btn(8) && !Joy1Btn(6))
		{
			motor[intakeMot] = -50;
		}
		else
		{
			motor[intakeMot] = 0;
		}
	}*/
}
