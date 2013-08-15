void showString(string str)
{
  nxtDisplayString(3, "%s", str);
  wait1Msec(50);
}


//NOTE: Notice how I commented out the main method from this program, because
//if you leave it and run Hi_import_test.c, then the compiler will see two mains,
//and freak out and complain about it.

/*task main()
{
  while(true)
  {
    string hi = "Hello, World!";
    string str2 = "beans";
    string str3 = "kjashdfja";
    string str4 = "theory";
    showString(hi);
    showString(str2);
    showString(str3);
    showString(str4);
  }
}*/
