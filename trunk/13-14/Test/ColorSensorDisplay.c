#pragma config(Sensor, S2,     colorSensor,    sensorCOLORFULL)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
	string sColor;
	while(true)
	{
    switch (SensorValue[colorSensor])
    {
      case BLACKCOLOR: sColor = "Black"; break;
      case BLUECOLOR: sColor = "Blue"; break;
      case GREENCOLOR: sColor = "Green"; break;
      case YELLOWCOLOR: sColor = "Yellow"; break;
      case REDCOLOR: sColor = "Red"; break;
      case WHITECOLOR: sColor = "White"; break;
      default: sColor = "???"; break;
    }
    nxtDisplayCenteredTextLine(2, sColor);
    wait1Msec(50);
	}
}