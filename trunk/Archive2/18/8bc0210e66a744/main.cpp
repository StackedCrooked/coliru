#include <iostream>
using namespace std;   
int main()
{
 int userInput = -2 ;
  /**** 3A. Student to fill in line of code for answer 3A ****/
   while(userInput <= 0)
   {/*while the number is 0 or positive*/
    cout << "Please input a negative, non-zero integer"<< endl;
   cin >> userInput;
   if(userInput<0)
   {/*Negative integer input*/
    cout << userInput << " is negative.  Thank you." << endl;
   } else {
    cout << userInput << " is a zero or positive.  Try again." << endl;
   }
  }
  cout << "Code completed with userInput = " << userInput << endl;
  return 0;
 }lkasd'pawd'jWDJOJ[-P  wo