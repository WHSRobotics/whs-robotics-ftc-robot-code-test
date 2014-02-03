 // comment out this to show the issue of not using a semaphore

#include "JoystickDriver.c"
 #define ENABLE_SEMAPHORES   1

// the semaphore variable
TSemaphore  MySemaphore;



task Task2()
{
    int     i = 0;

    while( true )
        {
#ifdef ENABLE_SEMAPHORES
        // Lock the semaphore - we will wait so no need for a timeout
        SemaphoreLock( MySemaphore );

#endif

getJoystickSettings(joystick);
        // Display the moving #
				if(Joy1Btn(1))
				{
					motor[motorA] = -100;
				}
				else
				{
					motor[motorA] = 0;
				}
        writeDebugStreamLine("2");

        // release the semaphore if we have it
        if ( bDoesTaskOwnSemaphore(MySemaphore) )
            SemaphoreUnlock(MySemaphore);

        // Sleep
        wait1Msec( 15 );
        }
}




/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*  A task to display a moving # on the upper row of the Vex Lcd               */
/*                                                                             */
/*-----------------------------------------------------------------------------*/

task Task1()
{
    int     i = 0;

    while( true )
        {
#ifdef ENABLE_SEMAPHORES
        // Lock the semaphore - we will wait so no need for a timeout
        SemaphoreLock( MySemaphore );

#endif
getJoystickSettings(joystick);
				if(joystick.joy1_TopHat == 0)
				{
					motor[motorA] = -100;
				}
				else
				{
					motor[motorA] = 0;
				}
        // Display the moving #
				writeDebugStreamLine("1");

        // release the semaphore if we have it
        if ( bDoesTaskOwnSemaphore(MySemaphore) )
            SemaphoreUnlock(MySemaphore);

        // Sleep
        wait1Msec( 500 );
        }
}

/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*  The main task,  display a moving x on the lower row of the Vex Lcd         */
/*                                                                             */
/*-----------------------------------------------------------------------------*/

task main()
{
    int     i = 0;


    // Init the semaphore
    SemaphoreInitialize(MySemaphore);

    // Start the other task
    StartTask( Task1 );
    StartTask(Task2);



    // Do our own thing
    while( true )
        {
#ifdef ENABLE_SEMAPHORES
        // Lock the semaphore - we will wait so no need for a timeout
        SemaphoreLock( MySemaphore );
#endif
				motor[motorA] = 50;
        writeDebugStreamLine("main");

        // release the semaphore if we have it
        if ( bDoesTaskOwnSemaphore(MySemaphore) )
            SemaphoreUnlock(MySemaphore);

        // Sleep
        wait1Msec( 50 );
        }
}


/*TSemaphore idk;

task MotorForward()
{
	while(true)
	{
#ifdef ENABLE_SEMAPHORES
		// Lock the semaphore - we will wait so no need for a timeout
		SemaphoreLock(idk);
#endif

		motor[motorA] = 100;
		writeDebugStreamLine("forward");

		// release the semaphore if we have it
		if ( bDoesTaskOwnSemaphore(idk) )
			SemaphoreUnlock(idk);

		// Sleep
		wait1Msec(500);
	}
}


task MotorBackward()
{
	while(true)
	{
#ifdef ENABLE_SEMAPHORES
		// Lock the semaphore - we will wait so no need for a timeout
		SemaphoreLock(idk);
#endif

		motor[motorA] = -100;
		writeDebugStreamLine("backward");

		// release the semaphore if we have it
		if ( bDoesTaskOwnSemaphore(idk) )
			SemaphoreUnlock(idk);

		// Sleep
		wait1Msec(500);
	}
}



task main()
{
	SemaphoreInitialize(idk);
	StartTask(MotorForward);
	StartTask(MotorBackward);
	while(true)
	{
#ifdef ENABLE_SEMAPHORES
		SemaphoreLock(idk);
#endif

		motor[motorA] = 0;
		writeDebugStreamLine("main");
		if ( bDoesTaskOwnSemaphore(idk) )
			SemaphoreUnlock(idk);
	}
	wait1Msec(50);
}*/
