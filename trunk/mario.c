/*
Q-A3, Q-G3, rest, Q-G3
H.-G3, H.-F3, H.-E3
Q-D3, Q-E2, Q-D2, Q-E2
Q-C2*/

const float C3 = 130.81;
const float D3 = 146.83;
const float E3 = 164.81;
const float D4 = 293.67;
const float E4 = 329.63;
const float F4 = 349.23;
const float G4 = 392.00;
const float A4 = 440.00;

const int HALF = 30;
const int HALF_DOT = 45;
const int QUARTER = 15;

void playNote(float freq, int length)
{
  PlayTone(freq, length);
  while(bSoundActive){};
}

task main()
{
  playNote(A4, QUARTER);
  playNote(G4, QUARTER);
  wait10Msec(QUARTER);
  playNote(G4, QUARTER);

  playNote(G4, HALF_DOT);
  playNote(F4, HALF_DOT);
  playNote(E4, HALF_DOT);

  playNote(D4, QUARTER);
  playNote(E3, QUARTER);
  playNote(D3, QUARTER);
  playNote(E3, QUARTER);

  playNote(C3, QUARTER);

}
