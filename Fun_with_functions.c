//B = right motor, C = left motor


//////////////////////////////////
//////----- Functions -----//////
////////////////////////////////

/*Note: Functions have this syntax:
returntype methodName(parameters)
{
  body;
}*/


/**This function causes the robot to perform
* a sharp right turn for 1 second.
* Return type void, because it doesn't return anything. */
void rightTurn()
{
  motor[motorC] = 100;
  motor[motorB] = 0;
  wait10Msec(100);
}


/**This function causes the robot to perform
* a sharp left turn for 1 second. */
void leftTurn()
{
  motor[motorC] = 0;
  motor[motorB] = 100;
  wait10Msec(100);
}


/**This function causes the robot
* to move straight for 1 second.
* Parameter is an integer, which will be used
* to determine the amount of power the robot uses. */
void moveStraight(int pow)
{
  motor[motorB] = pow;
  motor[motorC] = pow;
  wait1Msec(100);
}


/**Main function. The robot runs this. */
task main()
{
  //Call the functions.
  //This means that the robot looks at the code in the corresponding functions and run whatever's in it.
  rightTurn();
  leftTurn();

  //Notice how you put the parameter in when you call a function that needs a parameter.
  moveStraight(100);
  //In this case, the int pow will be set to 100 when the function is run (only this time).

  //You could call the same function again with another parameter.
  moveStraight(10);


  /*Expected movement of this program:
  1) Sharp right turn for 1 sec.
  2) Sharp left turn for 1 sec.
  3) Move straight at 100 power for 1 sec.
  4) Move straight at 10 power for 1 sec.
  5) Sit there and look pretty
  */
}
