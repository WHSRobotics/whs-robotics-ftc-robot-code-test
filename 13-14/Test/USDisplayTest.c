#pragma config(Hubs,  S1, HTMotor,  HTServo,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     US,             sensorSONAR)
#pragma config(Motor,  mtr_S1_C1_1,     L,             tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     R,             tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C2_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
int sum = 0;
int avg = 0;
task Average()
{
		for(int timeCount = 0; timeCount < 1000; timeCount++)
		{
			wait10Msec(1);
			if(SensorValue(US) > 0)// If the ultrasonic sensor greater than 0 then it will add the sensor value to the sum.
			{
				sum += SensorValue(US);
			}
			// The sum will be divided by 100 to get the average ultrasonic reading.
			//get sensor values from the ultrasonic sensor
			//add the sensor values with each other
			//get the sum
		}
		avg = sum / 1000;
		//divide by 100
}



int WaffleCount()
{
	bool isWaffle = false;
	int numWaffles = 0;
	ClearTimer(T1);

	while(time10[T1] < 1000)
	{
		if(SensorValue(US) > 12) //if block
		{
			wait1Msec(250);
			PlayTone(440,1);
			isWaffle = true;
			//do somethin to isWaffle
		}
		else//if not block
		{
			if(isWaffle)
			{
				numWaffles++;
				isWaffle = false;
			}
			//if there was a waffle:
			//count the waffle
			//if not, do nothing
		}
	}
	return numWaffles;
}

//First if the sensor value is greater than 11.
//Add one to the count
//Make a sound
//Display the count

int count = 0;

task DisplayUS()
{
		while(true)
	{
		nxtDisplayString(1, "US: %d", SensorValue[US]);
		nxtDisplayString(2, "WffCnt: %d", count);


		wait10Msec(10);
		eraseDisplay();
	}
}

task SoundPlay()
{
}

task Count()
{
	while(true)
	{ bool block = false;
		if(SensorValue(US) < 9)
		{
			count += 1;
		}
		else
		{
			count = count;
		}
	}
}

task main()
{
	StartTask(DisplayUS);
	StartTask(SoundPlay);
	StartTask(Count);
	StartTask(Average);

	motor[L] = 50;
	motor[R] = 50;

	int numWaffles = WaffleCount();

	motor[L] = 0;
	motor[R] = 0;
	//display USSR average
	while(true)
	{
		nxtDisplayString(3, "avg: %d", avg);
		nxtDisplayString(4, "WaffleCount: %d", numWaffles);
	}
}
