#include <iostream>
#include <math.h>
#include <string>

using namespace std;

//Declare variables and constants.
float x, log_8_x;

int main()
{

//Prompt user to input number.
cout << "This program will calculate the log base 8 of a number. Input number to calculate" << endl;
cin >> x;

//Calculate log_8_x.
log_8_x = log(x) / log(8);

//Print log_8_x.
cout << "The log base 8 of " << x << " is " << log_8_x << endl;

//End main.
return (0);

}