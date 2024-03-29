#pragma config(Hubs,  S1, HTMotor,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     excel,          sensorI2CCustom)
#pragma config(Motor,  mtr_S1_C1_1,     leftDrive,     tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     rightDrive,    tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard   no it wasn't            !!*//

//#include "JoystickDriver.c";
#include "hitechnic-accelerometer.h";

int excel_x_raw = 0;
int excel_y_raw = 0;
int excel_z_raw = 0;
float excel_x = 0.0;
float excel_y = 0.0;
float excel_z = 0.0;
float excel_x_off = 0.0;
float excel_y_off = 0.0;
float excel_z_off = 0.0;
const float GRAVY = 0.0980665; //cm/m^s
float y = 0.0;                // create and set 'y' to 0.0
float LCD_width = 100.0;      // create and set 'LCD_width' to 100.0 (width of NXT LCD in pixels)
	bool XisG = false;
	bool YisG = false;
	bool ZisG = false;

void initializeRobot()
{
	int excel_x_sum = 0;
	int excel_y_sum = 0;
	int excel_z_sum = 0;

	HTACreadAllAxes(excel,excel_x_raw,excel_y_raw,excel_z_raw);
	if(excel_x_raw > 190)
	{
		XisG = true;
	}
	if(excel_y_raw > 190)
	{
		YisG = true;
	}
	if(excel_z_raw > 190)
	{
		ZisG = true;
	}

	for(int count = 0; count < 100; count++)
	{
		HTACreadAllAxes(excel,excel_x_raw,excel_y_raw,excel_z_raw);
		excel_x_sum += excel_x_raw;
		excel_y_sum += excel_y_raw;
		excel_z_sum += excel_z_raw;
		wait1Msec(5);
	}

	excel_x_off = excel_x_sum / 100.0;
	excel_y_off = excel_y_sum / 100.0;
	excel_z_off = excel_z_sum / 100.0;
	if(XisG)
	{
		excel_x_off = 200.0 - excel_x_off;
	}
	if(YisG)
	{
		excel_y_off = 200.0 - excel_y_off;
	}
	if(ZisG)
	{
		excel_z_off = 200.0 - excel_z_off;
	}

	PlayTone(440,30);
}


float cms2Convert(float raw)
{
	return ((raw/100.0)/GRAVY);
}


task UpdateExcel()
{
	while(true)
	{
		HTACreadAllAxes(excel,excel_x_raw,excel_y_raw,excel_z_raw); // calculate y-coordinate of pixel to draw
		excel_x = cms2Convert(excel_x_raw) - cms2Convert(excel_x_off);
		excel_y = cms2Convert(excel_y_raw) - cms2Convert(excel_y_off);
		excel_z = cms2Convert(excel_z_raw) - cms2Convert(excel_z_off);
		if(XisG)
		{
			excel_x -= 20.0;
		}
		if(YisG)
		{
			excel_y -= 20.0;
		}
		if(ZisG)
		{
			excel_z -= 20.0;
		}
	}
}



task Graph()
{
	//just for y axis for now

 	while(true)
 	{
		nxtDrawLine(0, 31, 99, 31);   // draw a line across the center of the LCD

		for(int x = 0; x < 2000; x++)  // loop from 0 to 99
		{
		  nxtSetPixel(x/20.0, excel_y + 31);                   // draw pixel at (x, y+31)
		}
		eraseDisplay();
	}

}

void runDrive(float power)
{
	motor[leftDrive] = power;
	motor[rightDrive] = power;
}


//time == Msec
void rampDrive(float maxPwr, float time)
{
	float rampTime = time*0.2; //one ramp time
	float maxPwrTime = time - rampTime*2.0;
	float currPow = 0.0;
	float lineIncrement = maxPwr/rampTime;

	for(float rampUpTime = 0.0; rampUpTime < rampTime; rampUpTime++) //ramp up
	{
		currPow += lineIncrement;
		runDrive(currPow);
		wait1Msec(lineIncrement);
	}
	for(float maxPowTime = 0.0; maxPowTime < maxPwrTime; maxPowTime++) //max pow
	{
		currPow = maxPwr;
		runDrive(currPow);
		wait1Msec(1);
	}
	for(float rampDownTime = 0.0; rampDownTime < rampTime; rampDownTime++) //ramp down
	{
		currPow -= lineIncrement;
		runDrive(currPow);
		wait1Msec(lineIncrement);
	}

	runDrive(0); //stop the drive train
}


void cosineRamp(int time , float maxPwr, float initPwr)
{
	float period = 2 * PI / time;
	ClearTimer(T1);
	while(time100[T1] <= time)
	{
		float power = -maxPwr * cos(period * time100[T1]) + maxPwr + initPwr;
		motor[leftDrive] = power;
		motor[rightDrive] = power;
	}
}


task Values()
{
	while(true)
	{
		eraseDisplay();

		nxtDisplayString(3,"x: %d", excel_x);
		nxtDisplayString(4,"y: %d", excel_y);
		nxtDisplayString(5,"z: %d", excel_z);
		wait1Msec(25);
	}
}


task main()
{
	initializeRobot();
	StartTask(UpdateExcel);
	//StartTask(Graph);
	StartTask(Values);
	ClearTimer(T1);
	while(true)//time100[T1] <= 20)
	{
		//float power = 50.0*sin(time100[T1]/5.0);
		//motor[leftDrive] = power;
		//motor[rightDrive] = power;
	}
	/*while(true)
	{
		getJoystickSettings(joystick);
		if(joystick.joy1_TopHat == 0)// && !joystick.joy1_TopHat == 4)
		{
			runDrive(100);
		}
		else if(joystick.joy1_TopHat == 4 && !joystick.joy1_TopHat == 0)
		{
			runDrive(-100);
		}
		else
		{
			runDrive(0);
		}
	}*/
	//cosineRamp(30 , -20.0, -10);
}
