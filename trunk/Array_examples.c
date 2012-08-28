const int NXT_DISPLAY_END = 80;
const int X_COORD_INCREMENT = 20;

task main()
{
  int values[5]; //create an array called "values" with 5 integers

  //To set all elements in the array to 30:
    for(int index = 0; index < 5; index++) //For each element in the array (0, 1, 2, 3, 4)
    {
      values[index] = 30; //Set the element at this particular index number to 30.
    }
    /*The array currently looks like: [30, 30, 30, 30, 30]
    *    corresponding index numbers:  0,  1,  2,  3,  4 */

    //To access a specific element in the array:
    int thirdElement = values[2]; //the variable thirdElement is set to the third element in the array, which is 30.
    /*Remember that array numbering starts from 0, so it makes sense that values[2] is the THIRD element
    * and values[3] is actually the FOURTH element. */

    //To set an element in an array to something:
    values[4] = 50; //Set the FIFTH element in the array to 50.
    /*The array currently looks like: [30, 30, 30, 30, 50]
    *    corresponding index numbers:   0,  1,  2,  3,  4
    * NOTE: values[5] does NOT exist!!! The array, although having 5 elements, only goes up to 4
    *       because it starts at 0. */


    //To display the array on NXT screen:
  while(true) //infinite loop
  {
    int val = 0; //what index are we going to get?

    for(int x = 0; x <= NXT_DISPLAY_END; x += X_COORD_INCREMENT) //x coordinate on NXT display. This would be x = 0, 20, 40, 60, 80
    {
      nxtDisplayStringAt(x,31, "%d", values[val]); //Display the element with the index number "val" at the coordinate (x, 31)
      //NOTE: "%d" is the specifier for ints; you put that there so the compiler knows what kind of data type it's dealing with.

      val++; //+1 to val (go on to the element in the array, by increasing the index number)
    }
  }
}




//-------------------------------Other fun things to do with arrays!---------------------------------

int coolArray[4]; //Create a global array with 4 elements.
int arraySize = 4; //variable to clarify the # of elements in array


//To initialize an array (fill it) with 4 consecutive odd numbers from 1 to 7:
/*** Pseudocode: (read through this after looking at the code)
* (1) Initialize a variable for the value to put in the array.
* (2) Create a for loop going through all elements of the array.
*     Start at index value 0. Set endpoint to # of elements in array (use LESS THAN). Increment index by 1.
* (2a) In this for loop, set the element at the array's index to the variable that you made earlier.
* (2b) Increment the variable that you made if needed.
*/
void initArray()
{
  int stuffing = 1; //(STEP 1) element to stuff into the cool array

  for(int index = 0; index < arraySize; index++) //(STEP 2) For each element in the array (indexes 0,1,2,3)
  {
    coolArray[index] = stuffing; //(STEP 2a) set the element at this index number to the variable stuffing.
    stuffing += 2; //(STEP 2b) add 2 to stuffing. This is the same as stuffing = stuffing + 2;
  }

  /* The painful process of tracing (working through a loop by hand):
  * (1) index = 0 (still less than 4), stuffing = 1. First element in the array is set to 1 (coolArray[0] = 1;)
  *     Add 2 to stuffing. stuffing is now equal to 3.
  *
  * (2) Add 1 to index. index = 1 (still less than 4), stuffing = 3.
  *     Second element in the array is set to 3 (coolArray[1] = 3;) Add 2 to stuffing. stuffing is now equal to 5.
  *
  * (3) +1 to index. index = 2 (still < 4), stuffing = 5. coolArray[2] = 5;
  *     +2 to stuffing. stuffing = 7.
  *
  * (4) +1 to index. index = 3 (still < 4), stuffing = 7. coolArray[3] = 7;
  *     +2 to stuffing. stuffing = 9.
  *
  * (5) +1 to index. index = 4 (NOT < 4). END. HOORAYYYYYYYYYY
  * The array coolArray[] now contains: [1, 3, 5, 7] */
}


//To calculate the sum of an array:
/*** Pseudocode:
* (1) Initialize a variable to hold the sum.
* (2) Make a for loop to go through all elements in the array
* (3) Add whatever element in coolArray for current inedx to the value sum.
*/
int calcSum()
{
  int sum = 0; //STEP 1

  for(int index = 0; index < arraySize; index++) //STEP 2
  {
    sum += coolArray[index]; //STEP 3
  }

  return sum; //return the sum
}


//To get the average of an array:
/*** Pseudocode:
* (1) Get sum of array (done in function calcSum())
* (2) Divide sum by # of elements in array
* Hooray */
int getAvg()
{
  int average = calcSum() / arraySize; //get sum returned in calcSum() and divide it by array size (4 elements)
  return average; //return the average
}
