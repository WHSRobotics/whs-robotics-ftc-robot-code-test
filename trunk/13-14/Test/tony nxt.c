
task main()
{

	while(true)
	{
		if(nNxtButtonPressed == 2) //left arrow
		{
			motor[motorA] = -100;
		}
		else if(nNxtButtonPressed == 1)
		{
			motor[motorA] = 100;
		}
		else if(nNxtButtonPressed == 3)
		{
			motor[motorA] = 50;
		}
		motor[motorA] = 0;
	}


}
