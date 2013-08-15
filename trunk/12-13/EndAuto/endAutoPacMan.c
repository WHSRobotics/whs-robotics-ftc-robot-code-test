/*task EndAuto()
{
  ClearTimer(T2);

  if(time100[T2] > 270)
  {
    PlaySoundFile("pac1.rso");
    while(bSoundActive){};

	  PlaySoundFile("pac2.rso");
	  while(bSoundActive){};

	  PlaySoundFile("pac3.rso");
	  while(bSoundActive){};

	  PlaySoundFile("pac4.rso");
	  while(bSoundActive){};

	  StopTask(EndAuto);
  }
  return;
}
*/
task main()
{
  PlaySoundFile("pac1.rso");
  while(bSoundActive){};

  PlaySoundFile("pac2.rso");
  while(bSoundActive){};

  PlaySoundFile("pac3.rso");
  while(bSoundActive){};

  PlaySoundFile("pac4.rso");
  while(bSoundActive){};

}
