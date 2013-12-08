//StopRamming pseudocode
/*ClearTimer(T1);
while(encoders have not reached target)
{
	if(excel has significant negative spike)
	{
	  if(time100[T1] > estimatedTime)
	  {
	  	stopDriveTrain();
	  }
	}
}
*/

const int SPIKE_THRESH = 8;
//need to find equation for estTime experimentally
int estTime = 0;
while(nMotorRunState[leftDrive] != runStateIdle && nMotorRunState[rightDrive] != runStateIdle)
{
	if(abs(SensorValue[excel]) > SPIKE_THRESH)
	{
		if(time100[T1] > estTime)
		{
			stopDriveTrain();
		}
	}
}
