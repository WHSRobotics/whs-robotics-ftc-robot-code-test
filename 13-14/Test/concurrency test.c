#pragma config(Motor,  motorA,          grayMot,       tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          blackMot,      tmotorNXT, PIDControl, reversed, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

bool needArm = false;

task Arm()
{
	while(true)
	{
		if(needArm)
		{
			motor[grayMot] = 100;
			wait1Msec(2000);
			//needArm = false;
			motor[grayMot] = 0;
			return;
		}
		PlayTone(400,1);
	}
}


task main()
{
	StartTask(Arm);
	motor[blackMot] = 100;
	wait1Msec(5000);
	needArm = true;
	motor[blackMot] = 0;
	wait1Msec(5000);

}
