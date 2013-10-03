
task main()
{
float y = 0.0;                // create and set 'y' to 0.0
float LCD_width = 100.0;      // create and set 'LCD_width' to 100.0 (width of NXT LCD in pixels)
 while(true){
nxtDrawLine(0, 31, 99, 31);   // draw a line across the center of the LCD

for(int x = 0; x < 100; x++)  // loop from 0 to 99
{
  y = sin(x * (2.0 * PI) / LCD_width) * 25; // calculate y-coordinate of pixel to draw
  nxtSetPixel(x, y + 31);                   // draw pixel at (x, y+31)
  wait1Msec(100);                           // wait 100 milliseconds
}

}
}
