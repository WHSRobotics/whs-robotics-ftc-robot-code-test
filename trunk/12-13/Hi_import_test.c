#include "hello_world.c"; //import the file called "hello_world.c"
//NOTE: Put the file name in quotation marks, because it's a string!
//NOTE #2: Make sure the file you're importing doesn't have a task main(), or else it won't compile
//NOTE #3: Don't forget the ; hahha

task main()
{
  while(true) //infinite loop
  {
    //declare a bunch of strings
    string hi = "Hello, World!";
    string str2 = "beans";
    string str3 = "kjashdfja";
    string str4 = "theory";

    //use the method showString (from the file "hello_world.c")
    showString(hi);
    showString(str2);
    showString(str3);
    showString(str4);
  }
}
