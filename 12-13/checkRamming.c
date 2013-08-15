float leftEncoderPrev = 0.0;
float rightEncoderPrev = 0.0;
float leftEncoderCurr = 0.0;
float rightEncoderCurr = 0.0;
float leftEncoderDiff = 0.0;
float rightEncoderDiff = 0.0;
float leftEncoderRate = 0.0;
float rightEncoderRate = 0.0;
float leftEncoderError = 0.0;
float rightEncoderError = 0.0;
const float CHANGE_AVG_RATE = 42.0; //magic num
const float THRESHOLD = 5.0; //magic num
const float TIME_INTERVAL = 100.0; //magic num

bool leftFinished = (nMotorRunState[driveLeft] == runStateIdle);
bool rightFinished = (nMotorRunState[driveRight] == runStateIdle);


void CheckRamming()
{
  //reset encoder values
  nMotorEncoder[driveLeft] = 0;
  nMotorEncoder[driveRight] = 0;

  //check if encoders have reached their target
  leftFinished = (nMotorRunState[driveLeft] == runStateIdle);
  rightFinished = (nMotorRunState[driveRight] == runStateIdle);

  ClearTimer(T1);
  while(!leftFinished && !rightFinished)
  {
    //while encoders still have not reached their target
    if(time1[T1] >= TIME_INTERVAL) //if 100 Msec have passed
    {
      //get both encoder values
	    leftEncoderCurr = nMotorEncoder[driveLeft];
	    rightEncoderCurr = nMotorEncoder[driveRight];

	    leftEncoderDiff = leftEncoderCurr - leftEncoderPrev;
	    rightEncoderDiff = rightEncoderCurr - rightEncoderPrev;

	    //calculate encoder counts per 100 Msec for both encoders
	    leftEncoderRate = leftEncoderDiff / TIME_INTERVAL;
	    rightEncoderRate = rightEncoderDiff / TIME_INTERVAL;

	    //calculate error between current rates and avg rates
	    leftError = abs(leftEncoderRate - CHANGE_AVG_RATE);
	    rightError = abs(rightEncoderRate - CHANGE_AVG_RATE);

	    if(leftError > THRESHOLD || rightError > THRESHOLD)
	    {
	      //if current rates are significantly different from average
	      //(the robot is ramming something else)

	      //back up at full power for 500 Msec
	      motor[driveLeft] = -100;
	      motor[driveRight] = -100;

	      wait1Msec(500);

	      //stop the drive train
	      motor[driveLeft] = 0;
	      motor[driveRight] = 0;
	    }

	    //reset timers and encoders
	    ClearTimer(T1);

	    leftEncoderPrev = leftEncoderCurr;
	    rightEncoderPrev = rightEncoderCurr;

	    break;

  }
 }
}
