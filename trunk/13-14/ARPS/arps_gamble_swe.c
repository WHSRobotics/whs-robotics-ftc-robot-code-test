//#include "whateverItMayBe"



task main()
{
	waitForStart();
	raiseArm = true;
	wait1Msec(300);
	if(SensorValue[IRSensor] <= 4 && SensorValue[IRSensor] != 0)
	{
		crate = 1;
	}
	else if(SensorValue[IRSensor] == 5)
	{
		crate = 2;
	}
	else if(SensorValue[IRSensor] == 0)//added in SensorValue, it caused everything to go wrong
	{
		crate = 3;
	}
	//---Move forward
	//---Move towards the ramp by having servos turn and then moving forward

	if(crate == 2)							//this crate would have to be the closest one to us
	{
		motor[sweBL] = 100;				//motors would be going at 100 power
		motor[sweBR] = 100;
		motor[sweFL] = 100;
		motor[sweFR] = 100;
		wait1Msec(1000);					//the robot will be going forward for 1 second
															//turntable will turn 90 degrees to the right
															//drop the cube into the second crate
	}
	else if(crate == 3)
	{
		motor[sweBL] = 100;				//motors would be going at 100 power
		motor[sweBR] = 100;
		motor[sweFL] = 100;
		motor[sweFR] = 100;
		wait1Msec(1500);					//the robot will be going forward for 1.5 second
															//turntable will turn 90 degrees to the right
															//drop the cube into the third crate
	}
	else
	{
															//turntable will turn 90 degrees to the right
															//drop the cube into the first crate
	}
}
