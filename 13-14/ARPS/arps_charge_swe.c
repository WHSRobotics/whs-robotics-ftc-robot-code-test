
bool raiseArm = false;

/////////DUMP AUTONOMOUS/////////


task main()
{
	waitForStart;

	raiseArm = true;
	wait1Msec(100);
	servo[swiBL] = lessturn; //turn about 30 degrees
	servo[swiBR] = lessturn; //turn about 30 degrees
	servo[swiFL] = lessturn; //turn about 30 degrees
	servo[swiFR] = lessturn; //turn about 30 degrees
	motor[sweBL] = 100;	     //have the motor go at 100 power
	motor[sweBR] = 100;	     //have the motor go at 100 power
	motor[sweFL] = 100;	     //have the motor go at 100 power
	motor[sweFR] = 100;	     //have the motor go at 100 power
	wait1Msec(1000); 				 //move forward for 1 second
	return;
}
