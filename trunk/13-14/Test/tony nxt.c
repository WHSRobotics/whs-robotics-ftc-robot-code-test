
task main()
{

	while(true)
	{
		if(nNxtButtonPressed == 2) //left arrow
		{
			motor[motorC] = -100;
		}
		else if(nNxtButtonPressed == 1)
		{
			motor[motorC] = 100;
		}
		else if(nNxtButtonPressed == 3)
		{
			motor[motorC] = 50;
		}
		motor[motorC] = 0;
	}


}
