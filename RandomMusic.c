const float G4 = 391.995;
const float A4 = 	440.000;
const float B4 = 493.883;
const float C5 = 523.251;
const float D5 = 587.330;
const float E5 = 659.255;
const float D4 = 293.665;

const int QUARTER_NOTE = 30;
const int EIGHTH_NOTE = 15;
const int HALF_NOTE = 45;


void playNote(float freq, int length)
{
  PlayTone(freq, length);
  while(bSoundActive){};
}


void first()
{
  playNote(G4, QUARTER_NOTE);
  playNote(A4, QUARTER_NOTE);
  playNote(B4, QUARTER_NOTE);
  playNote(G4, QUARTER_NOTE);
}

void second()
{
  playNote(B4, QUARTER_NOTE);
  playNote(C5, QUARTER_NOTE);
  playNote(D5, HALF_NOTE);
}

void third()
{
  playNote(D5, EIGHTH_NOTE);
  playNote(E5, EIGHTH_NOTE);
  playNote(D5, EIGHTH_NOTE);
  playNote(C5, EIGHTH_NOTE);
  playNote(B4, QUARTER_NOTE);
  playNote(G4, QUARTER_NOTE);
}

void fourth()
{
  playNote(G4, QUARTER_NOTE);
  playNote(D4, QUARTER_NOTE);
  playNote(G4, HALF_NOTE);
}

task main ()
{
  first();
  first();
  second();
  second();
  third();
  third();
  fourth();
  fourth();
}
