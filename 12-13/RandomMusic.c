const float G4 = 391.995;
const float A4 = 	440.000;
const float B4 = 493.883;
const float C4 = 261.626;
const float Cs4 = 277.183;
const float Cs5 = 554.365;
const float C5 = 523.251;
const float E4 = 329.628;
const float D5 = 587.330;
const float Fs4 = 369.994;
const float E5 = 659.255;
const float D4 = 293.665;
const float Fs5 = 739.989;
const float Gs4 = 415.305;
const float F4 = 349.228;


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


void whsFirst()
{
  playNote(A4, 70);
  playNote(B4, 40);
  playNote(Cs5, 40);
  playNote(A4, 60);

  playNote(A4, 60);
  playNote(G4, 40);
  playNote(G4, 40);
  playNote(F4, 60);

  playNote(B4, 60);
  playNote(Cs5, 50);
  playNote(D5, 50);
  playNote(Gs4, 60);
  playNote(A4, 70);
}


task main()
{
  whsFirst();
  /*first();
  first();
  second();
  second();
  third();
  third();
  fourth();
  fourth();*/
}
