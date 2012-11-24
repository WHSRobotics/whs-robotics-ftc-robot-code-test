/*
H-A3, H-G3, rest, H-G3
H.-G3, H.-F3, H.-E3
H-D3, H-E2, H-D2, H-E2
H-C2*/

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
  playNote(A3, HALF);
  playNote(G3, HALF);
  wait10Msec(45);
  playNote(G3, HALF);

  playNote(G3, HALF_DOT);
  playNote(F3, HALF_DOT);
  playNote(E3, HALF_DOT);

  playNote(D3, HALF_DOT);
  playNote(E2, HALF_DOT);
  playNote(D2, HALF_DOT);
  playNote(E2, HALF_DOT);

  playNote(C2, HALF);

}
