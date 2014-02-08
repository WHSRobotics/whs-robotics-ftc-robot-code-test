#include "auto_globVars_swedr.h"
#include "arps_functions_swedr.h"

task main()
{
	intitializeRobotCarasoul;
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
		moveStraight(90.0, 30.0, 100)				//motors would be going at 100 power
		gyroCenterPivot(90, 100)
		dropTheBlock;												//drop the cube into the second crate
	}
	else if(crate == 3)
	{
		moveStraight(90.0, 40.0, 100)				//motors would be going at 100 power
		gyroCenterPivot(90, 100)						//robot will turn 90 degrees to the right
		dropTheBlock;												//drop the cube into the third crate
	}
	else
	{
		moveStraight(90.0, 15.0, 100)				//Robot will go forward for 15 inches at 100 power.
		gyroCenterPivot(90, 100)						//robot will turn 90 degrees to the right
		dropTheBlock;												//drop the cube into the first crate
	}
	moveArm(50);
	moveStraight(90.0,
//Raise the arm
//Have the servos and towards the crate
//Move forward
//Swivel around
//Drop the cube into the crate
//Then have the servos angled towards the opposite side of the ramp
//Move forward

}
