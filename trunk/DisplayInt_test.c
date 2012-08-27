task main()
{
  int values[5];
    for(int index = 0; index < 5; index++)
    {
      values[index] = 30;
    }
  while(true)
  {
    int val = 0;
    for(int x = 0; x <= 80; x += 20)
    {
      nxtDisplayStringAt(x,31, "%d", values[val]);
      val++;
    }
  }
}
