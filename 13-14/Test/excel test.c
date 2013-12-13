#pragma config(Sensor, S1,     excel,          sensorI2CCustom)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "hitechnic-accelerometer.h";

task main()
{
	int x;
	int y;
	int z;
	while(true)
	{
		HTACreadAllAxes(excel,x,y,z);

		eraseDisplay();
		nxtDisplayString(3,"x: %d", x);
		nxtDisplayString(4,"y: %d", y);
		nxtDisplayString(5,"z: %d", z);

	}
}