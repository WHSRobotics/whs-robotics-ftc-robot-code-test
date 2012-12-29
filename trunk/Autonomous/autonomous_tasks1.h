#ifndef AUTONOMOUS_TASKS1.H;
#define AUTONOMOUS_TASKS1.H;

//------------------notes--------------------
const float As3 = 233.08*2;
const float A3 = 220.00*2;
const float B3 = 246.94*2;
const float Cs3 = 138.59*2;
const float Cs4 = 277.18*2;
const float C3 = 130.81*2;
const float C4 = 261.63*2;
const float Ds3 = 155.56*2;
const float D3 = 146.83*2;
const float D4 = 293.67*2;
const float E3 = 164.81*2;
const float E4 = 329.63*2;
const float Fs3 = 185.00*2;
const float Fs4 = 369.99*2;
const float F3 = 174.61*2;
const float F4 = 349.23*2;
const float G3 = 196.00*2;
const float G4 = 392.00*2;

//-------------------time---------------------
const int QUARTER = 36;
const int QUARTER_DOT = 54;
const int WHOLE = 144;
const int HALF = 72;
const int HALF_DOT = 108;
const int EIGHTH = 18;


//------------------functions-----------------
void playNote(float freq, int length)
{
  PlayTone(freq, length);
  while(bSoundActive){};
}


void first()
{
  playNote(B3, QUARTER);
  playNote(G3, EIGHTH);
  playNote(C4, QUARTER);
  playNote(G3, EIGHTH);
  playNote(Cs4, QUARTER);

  playNote(G3, EIGHTH);
  playNote(D4, WHOLE);

  playNote(E4, EIGHTH);
  playNote(B3, QUARTER);
  playNote(D4, WHOLE);
  wait10Msec(QUARTER);

  playNote(D4, EIGHTH);
  playNote(E4, QUARTER);
  playNote(B3, QUARTER);

  playNote(D4, HALF);
  playNote(C4, QUARTER);
  playNote(F3, WHOLE);
  wait10Msec(QUARTER);

  playNote(D4, QUARTER);
  playNote(Cs4, EIGHTH);
  playNote(C4, QUARTER);
}


void second()
{
  playNote(B3, EIGHTH);
  playNote(A3, WHOLE);
  wait10Msec(QUARTER);

  playNote(B3, EIGHTH);
  playNote(Fs3, QUARTER);
  playNote(A3, WHOLE);
  wait10Msec(QUARTER);

  playNote(A3, QUARTER);
  playNote(B3, EIGHTH);
  playNote(Fs3, QUARTER);

  playNote(A3, HALF);
  playNote(G3, EIGHTH);
  playNote(C3, QUARTER);
  wait10Msec(QUARTER);

  playNote(C3, QUARTER);
  playNote(Cs3, QUARTER);
  playNote(D3, QUARTER);

  playNote(Ds3, EIGHTH);
  playNote(E3, HALF_DOT);
  playNote(E4, QUARTER_DOT);

  playNote(D4, QUARTER);
  playNote(C4, WHOLE);
  wait10Msec(QUARTER);

  playNote(B3, EIGHTH);
  playNote(A3, QUARTER);
}


void third()
{
  playNote(G3, EIGHTH);
  playNote(Fs3, QUARTER_DOT);
  playNote(B3, HALF);

  playNote(Fs3, EIGHTH);
  playNote(A3, QUARTER);
  playNote(G3, WHOLE);
  wait10Msec(QUARTER);

  playNote(E3, QUARTER);
  playNote(G3, QUARTER);
  playNote(B3, QUARTER);
  playNote(E4, QUARTER);

  playNote(Fs4, EIGHTH);
  playNote(G4, HALF_DOT);
  wait10Msec(QUARTER);
  playNote(E4, QUARTER);

  playNote(G4, EIGHTH);
  playNote(Fs4, QUARTER);
  playNote(E4, EIGHTH);
  playNote(F4, QUARTER);
  playNote(B3, QUARTER);

  playNote(Fs4, QUARTER_DOT);
  playNote(F4, EIGHTH);
  playNote(E4, QUARTER);
  playNote(F4, EIGHTH);

  playNote(C4, EIGHTH);
  playNote(E4, QUARTER);
  playNote(As3, QUARTER);
  playNote(E4, QUARTER_DOT);

  playNote(E4, EIGHTH);
  playNote(D4, QUARTER);
  playNote(Cs4, EIGHTH);
  playNote(D4, QUARTER);
}


//----------------------tasks---------------------
task ElevatorMusic()
{
  bool flamingo = true;
  bool blownUp = true;

  while(flamingo == blownUp)
  {
    first();
    second();
    third();
  }
}



task Flags()
{
	while(true)
	{
		motor[flagLeft] = 50;
		motor[flagRight] = 50;
		wait10Msec(21);
		motor[flagLeft] = -50;
		motor[flagRight] = -50;
		wait10Msec(21);
	}
}


#endif
