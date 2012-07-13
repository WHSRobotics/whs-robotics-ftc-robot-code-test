//B is right motor, C is left
//S1 touch, S2 compass, S3 light, S4 ultrasonic



//////////////////////////////////////////////////
//-----------------Basic Methods----------------//
//////////////////////////////////////////////////

void turn(int bPow, int cPow, int amtTime) //turn, given power for motors B and C and length of time
{
  motor[motorB] = bPow;
  motor[motorC] = cPow;
  wait1Msec(amtTime);
}


void moveStraight(int pow, int amtTime) //move straight, given power and length of time
{
  motor[motorB] = pow;
  motor[motorC] = pow;
  wait1Msec(amtTime);
}


void lineFollow()
{
  if(SensorValue[S3] < 20) //if black
  {
    turn(30,50,50); //turn right until white
  }
  else if(SensorValue[S3] > 80) //if white
  {
    turn(50,30,50); //turn left until black
  }
  else //if in between
  {
    moveStraight(70,50); //go straight
  }
}


void fowTouchWall(int pow) //move forward for given power until hit wall
{
  while(SensorValue[S1] == 0)
  {
    moveStraight(pow,50);
   }
}


void fowSonicWall(int pow, int dist) //move forward for given power until given distance (cm)
{
  while(SensorValue[S4] > dist)
  {
    moveStraight(pow,50);
  }
}


void turnCompass(bool turnLeft, string dir) //turn left or right until facing desired direction
{
  int deg = 0;

  //Set target degrees based on direction name
  if(dir == "east")
  {
    deg = 90;
  }
  else if(dir == "south")
  {
    deg = 180;
  }
  else if(dir == "west")
  {
    deg = 270;
  }

  while(SensorValue[S2] > deg + 20 || SensorValue[S2] < deg - 20) //while compass is outside threshold of (deg-20)<x<(deg+20)
  {
    if(turnLeft) //turn as specified (left) until in threshold
    {
      turn(70,0,50);
    }
    else //... or turn right until threshold
    {
      turn(0,70,50);
    }
  }
}



//////////////////////////////////////////////////
//--------Methods more specific to field--------//
//////////////////////////////////////////////////

void firstFollow() //get onto the line
{
  while(SensorValue[S3] > 40)
  {
    turn(0, 50, 50); //turn right until see black
  }

  while(SensorValue[S1] == 0) //follow line until hit wall
  {
    lineFollow();
  }
}


void toOpening() //get to the opening
{
  moveStraight(-70,1000); // move back from wall
  turnCompass(true, "north"); //turn left until facing north

  moveStraight(70,4000); //move forward to opening
  turnCompass(false,"east"); //turn right until facing east

  fowTouchWall(70); //move forward until touch wall
  moveStraight(-70,1000); //move back from wall
}


void throughMaze() //navigate through maze
{
  turnCompass(false,"south"); //turn right until facing south
  fowSonicWall(70,30); //move forward until 30 cm away from wall

  turnCompass(true,"east"); //turn left until facing east
  fowTouchWall(70); //move forward until touch wall
  moveStraight(-70,1000); //move back from wall
}


void toFinish() //get to finish!
{
  turnCompass(true,"north"); //turn left until facing north
  fowTouchWall(70); //move forward until touch wall
}



//////////////////////////////////////////////////
//------------------Main Method-----------------//
//////////////////////////////////////////////////

task main()
{
  firstFollow();
  toOpening();
  throughMaze();
  toFinish();
}
