
//#include "whateverItMayBe"

bool raiseArm = false;

task main()
{
	waitForStart;

	raiseArm = true;
	wait1Msec(100);
	servo[swiBL] = moreturn; //turn about 60 degrees
	servo[swiBR] = moreturn; //turn about 60 degrees
	servo[swiFL] = moreturn; //turn about 60 degrees
	servo[swiFR] = moreturn; //turn about 60 degrees
	motor[sweBL] = 100;			 //have the motor go at 100 power
	motor[sweBR] = 100;			 //have the motor go at 100 power
	motor[sweFL] = 100;			 //have the motor go at 100 power
	motor[sweFR] = 100;			 //have the motor go at 100 power
	wait1Msec(1000);				 //have to robot go forward for 1 second
	return;
}
