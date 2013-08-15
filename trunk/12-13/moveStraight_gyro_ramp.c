#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S2,     SMUX,           sensorI2CCustom)
#pragma config(Sensor, S3,     TUX,            sensorHiTechnicTouchMux)
#pragma config(Sensor, S4,     gyroRobot,      sensorI2CHiTechnicGyro)
#pragma config(Motor,  motorA,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorB,          flagLeft,      tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          flagRight,     tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     driveRight,    tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     driveLeft,     tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     armRight,      tmotorTetrix, PIDControl, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     armLeft,       tmotorTetrix, PIDControl, encoder)


//-------------------global vars and KONSTANTS-----------------
float scurrentValue = 0.0;
const float INCH_ENCODERVALUE = 114.591559; //number of encoder values in one inch forward for a 4 inch wheel



//--------------------moveStraight function--------------------
void moveStraight(int pwr, float totalInches)
{
  //Move straight at full power 70% of inches (majorInches)
  //and gradually ramp down power 30% of inches (minorInches)
  float majorInches = totalInches * 0.7;
  float minorInches = totalInches * 0.3;

  float newPwr = 0.0; //pwr for minorInches stage
  float currInches = 0.0; //current amt of inches passed
  float incInches = 0.0; //inches increment
  float incEncoder = 0.0; //encoder values increment
  bool leftMaster = false; //read encoder value from left motor?

  //initialize encoders
  nMotorEncoder[driveLeft] = 0;
  nMotorEncoder[driveRight] = 0;

  //Major Inches stage
  while(currInches <= majorInches)
  {
    incInches = 0.1*majorInches; //set increment for Major Inches stage

    //adjust power to straighten movement
    scurrentValue = HTGyroreadRot(gyroRobot); //take gyro reading
    if(scurrentValue < -0.5) //turning left
    {
			pwrDriveLeft += 1; //turn right to compensate
			leftMaster = false; //read encoder value from right motor
		}
    else if(scurrentValue > 0.5) //turning right
    {
      pwrDriveRight += 1; //turn left to compensate
      leftMaster = true; //read encoder value from left motor
    }
    else if(pwrDriveLeft >= pwr || pwrDriveRight >= pwr) //going too fast
    {
      pwrDriveLeft -= 1; //slow down to compensate
			pwrDriveRight -= 1;
      leftMaster = true; //read encoder value from left motor
    }

    //set motors to changed pwrs
		motor[driveLeft] = pwrDriveLeft;
		motor[driveRight] = pwrDriveRight;

    incEncoder = incInches * INCH_ENCODERVALUE; //convert inches to encoder values
	  //set DT encoder value targets to converted inch distances
    nMotorEncoderTarget[driveLeft] = incEncoder;
	  nMotorEncoderTarget[driveRight] = incEncoder;

    if(leftMaster) //read encoder value from left DT motor encoder
    {
      while(nMotorRunState[driveLeft] != runStateIdle)
      {
        //do nothing
      }
    }
    else //read encoder value from right DT motor encoder
    {
      while(nMotorRunState[driveRight] != runStateIdle)
      {
        //do nothing
      }
    }

    currInches += incInches; //keep track of current amt of inches moved

    //reset encoder values
    nMotorEncoder[driveLeft] = 0;
    nMotorEncoder[driveRight] = 0;
  }

  currInches = 0; //reset currInches

  //Minor Inches stage
  while(currInches <= minorInches)
  {
    incInches = 0.1*minorInches; //set increment for Minor Inches stage

    //adjust power to straighten movement
    scurrentValue = HTGyroreadRot(gyroRobot); //take gyro reading
    if(scurrentValue < -0.5) //turning left
    {
			pwrDriveLeft += 1; //turn right to compensate
			leftMaster = false; //read encoder value from right motor
		}
    else if(scurrentValue > 0.5) //turning right
    {
      pwrDriveRight += 1; //turn left to compensate
      leftMaster = true; //read encoder value from left motor
    }
    else if(pwrDriveLeft >= pwr || pwrDriveRight >= pwr) //going too fast
    {
      pwrDriveLeft -= 1; //slow down to compensate
			pwrDriveRight -= 1;
      leftMaster = true; //read encoder value from left motor
    }

    newPwr = -(pwr/minorInches)*currInches + pwr; //for both motors

    //set motors to changed pwrs
    motor[driveLeft] = pwrDriveLeft;
		motor[driveRight] = pwrDriveRight;

    incEncoder = incInches * INCH_ENCODERVALUE; //convert inches to encoder values
    //set DT encoder value targets to converted inch distances
	  nMotorEncoderTarget[driveLeft] = incEncoder;
	  nMotorEncoderTarget[driveRight] = incEncoder;

    if(leftMaster) //read encoder value from left DT motor encoder
    {
      while(nMotorRunState[driveLeft] != runStateIdle)
      {
        //do nothing
      }
    }
    else //read encoder value from right DT motor encoder
    {
      while(nMotorRunState[driveRight] != runStateIdle)
      {
        //do nothing
      }
    }

    currInches += incInches; //keep track of current amt of inches moved

    //reset motor encoder values
    nMotorEncoder[driveLeft] = 0;
    nMotorEncoder[driveRight] = 0;
  }

  stopDriveTrain();
}



//-------------------------main---------------------
task main()
{
  moveStraight(30, 50.0);
}
