#ifndef EXCELDRIVER.H;
#define EXCELDRIVER.H;

#include "hitechnic-accelerometer.h";

int excel_x_raw = 0;
int excel_y_raw = 0;
int excel_z_raw = 0;
float excel_x = 0.0;
float excel_y = 0.0;
float excel_z = 0.0;
float excel_x_off = 0.0;
float excel_y_off = 0.0;
float excel_z_off = 0.0;
const float GRAVY = 0.0980665; //cm/m^s
float y = 0.0;                // create and set 'y' to 0.0
float LCD_width = 100.0;      // create and set 'LCD_width' to 100.0 (width of NXT LCD in pixels)
bool XisG = false;
bool YisG = false;
bool ZisG = false;


void initializeExcel()
{
		int excel_x_sum = 0;
	int excel_y_sum = 0;
	int excel_z_sum = 0;

	HTACreadAllAxes(excel,excel_x_raw,excel_y_raw,excel_z_raw);
	if(excel_x_raw > 190)
	{
		XisG = true;
	}
	if(excel_y_raw > 190)
	{
		YisG = true;
	}
	if(excel_z_raw > 190)
	{
		ZisG = true;
	}

	for(int count = 0; count < 100; count++)
	{
		HTACreadAllAxes(excel,excel_x_raw,excel_y_raw,excel_z_raw);
		excel_x_sum += excel_x_raw;
		excel_y_sum += excel_y_raw;
		excel_z_sum += excel_z_raw;
		wait1Msec(5);
	}

	excel_x_off = excel_x_sum / 100.0;
	excel_y_off = excel_y_sum / 100.0;
	excel_z_off = excel_z_sum / 100.0;
	if(XisG)
	{
		excel_x_off = 200.0 - excel_x_off;
	}
	if(YisG)
	{
		excel_y_off = 200.0 - excel_y_off;
	}
	if(ZisG)
	{
		excel_z_off = 200.0 - excel_z_off;
	}
}


float cms2Convert(float raw)
{
	return ((raw/100.0)/GRAVY);
}


void updateExcel()
{
	HTACreadAllAxes(excel,excel_x_raw,excel_y_raw,excel_z_raw); // calculate y-coordinate of pixel to draw
	excel_x = cms2Convert(excel_x_raw) - cms2Convert(excel_x_off);
	excel_y = cms2Convert(excel_y_raw) - cms2Convert(excel_y_off);
	excel_z = cms2Convert(excel_z_raw) - cms2Convert(excel_z_off);
	if(XisG)
	{
		excel_x -= 20.0;
	}
	if(YisG)
	{
		excel_y -= 20.0;
	}
	if(ZisG)
	{
		excel_z -= 20.0;
	}
}


void displayValues()
{
	eraseDisplay();
	nxtDisplayString(3,"x: %d", excel_x);
	nxtDisplayString(4,"y: %d", excel_y);
	nxtDisplayString(5,"z: %d", excel_z);
	wait1Msec(25);
}


void displayGraph(string dir)
{
	nxtDrawLine(0, 31, 99, 31);   // draw a line across the center of the LCD

	for(int x = 0; x < 2000; x++)  // loop from 0 to 99
	{
		if(dir == "x")
		{
	  	nxtSetPixel(x/20.0, excel_x + 31);
		}
		else if(dir == "y")
		{
			nxtSetPixel(x/20.0, excel_y + 31);
		}
		else if(dir == "z")
		{
			nxtSetPixel(x/20.0, excel_z + 31);
		}
		else
		{
			nxtDisplayString(3,"%s","Put in an axis!");
		}
	}
	eraseDisplay();
}

#endif;
