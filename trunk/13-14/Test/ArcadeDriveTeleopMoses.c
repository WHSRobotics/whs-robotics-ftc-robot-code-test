const int HI_THRESH = 25;
const int LOW_THRESH = 15;
const float MAG_THRESH = 128.0/sqrt(2.0);
const float JOY_SCALE = 25.0/32.0;
const float SERVO_MAP = 255.0/PI;

#include "JoystickDriver.c"

int magValue = 0;
int swervePow = 0;
int angle = 0;
int servoPos = 0;

//----ARCADE_DRIVE_CONFIG----//
//Joystick1: Angle and Velocity
//Joystick2: Rotation

task main()
{
	getJoystickSettings(joystick);
	while(true)
	{
		getJoystickSettings(joystick);
		nxtDisplayTextLine(1, "acos: %d", acos(joystick.joy1_x1/128.0));
		wait10Msec(10);
		eraseDisplay();
	}
}

/*
while(true)
{
	swervePow = joystick.joy1_y2 * JOY_SCALE;
	if( abs( joystick.joy1_y2 ) > LOW_THRESH )
	{
		motor[sweOn] = swervePow;
		motor[sweTw] = swervePow;
		motor[sweTh] = swervePow;
		motor[sweFo] = swervePow;
	}
	else
	{
		motor[sweOn] = 0;
		motor[sweTw] = 0;
		motor[sweTh] = 0;
		motor[sweFo] = 0;
	}
	magValue = sqrt(pow(joystick.joy1_y1, 2) + pow(joystick.joy1_x1, 2));
	angle = atan2( joystick.joy1_y1, joystick.joy1_x1);
	if( magValue > MAG_THRESH )
	{
		servo[swiOn] =
		servo[swiTw] =
	}
	else
	{
	}
}
*/
