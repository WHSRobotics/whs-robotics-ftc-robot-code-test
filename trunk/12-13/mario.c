/*
Q-B4, Q-F5, rest, Q-F5
20-F5, 20-E5, 20-D5
Q-C5, Q-E4, Q-G4, Q-E4
Q-C4*/

const float B4 = 493.88;
const float F5 = 698.46;
const float E5 = 659.26;
const float D5 = 587.33;
const float C5 = 523.25;
const float E4 = 329.63;
const float G4 = 392.00;
const float C4 = 261.63;

const int HALF = 30;
const int HALF_TUP = 20;
const int QUARTER = 15;

void playNote(float freq, int length)
{
  PlayTone(freq, length);
  while(bSoundActive){};
}

task main()
{
  playNote(B4, QUARTER);
  playNote(F5, QUARTER);
  wait10Msec(QUARTER);
  playNote(F5, QUARTER);

  playNote(F5, HALF_TUP);
  playNote(E5, HALF_TUP);
  playNote(D5, HALF_TUP);

  playNote(C5, QUARTER);
  playNote(E4, QUARTER);
  playNote(G4, QUARTER);
  playNote(E4, QUARTER);

  playNote(C4, QUARTER);

}
