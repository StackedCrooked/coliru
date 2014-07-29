#include <algorithm>
#include <locale>
#include <string>
#include <iostream>

using namespace std;

int main()
{
    int month = 0;
    int line = 0;
    int days = 0;
    int j = 0;
    int i = 0;
    int sd = 0;
    while (month <= 12)
    {
      if (month == 2)
        days = 28;
    
      else if (month == 4 || month == 6 || month == 9 || month == 11)
        days = 30;
    
      else days = 31;
    
      cout << endl << endl << endl;
    
      if (month == 1)
        cout << "      JANUARY 20XX    \n";
    
      else if (month == 2)
        cout << "      FEBRUARY 20XX    \n";
    
      else if (month == 3)
        cout << "      MARCH 20XX    \n";
    
      else if (month == 4)
        cout << "      APRIL 20XX    \n";
    
      else if (month == 5)
        cout << "      MAY 20XX    \n";
    
      else if (month == 6)
        cout << "      JUNE 20XX    \n";
    
      else if (month == 7)
        cout << "      JULY 20XX    \n";
    
      else if (month == 8)
        cout << "      AUGUST 20XX    \n";
    
      else if (month == 9)
        cout << "      SEPTEMBER 20XX    \n";
    
      else if (month == 10)
        cout << "      OCTOBER 20XX    \n";
    
      else if (month == 11)
        cout << "      NOV 20XX    \n";
    
      else if (month == 12)
        cout << "      DEC 20XX    \n";
    
      cout << "-   -   -   -   -   -   -\n";
      cout << "M   T   W   T   F   S   S\n";
      cout << "-   -   -   -   -   -   -\n";
    
      while (j < days) {
        for (i = 0; i < 7 && j <= days; i++) { //i from 0to 6 for 7 days.j from 1 to no. of
          //days in the month
          if ((line == 1) && (i < sd))     //line =1 so that space is only in first line
            cout << "    ";
          else {
            cout << j << "  ";
            j++;
    
            if (i == 6) {
              cout << endl;
              line++;
            }
          }
        }
      }
    
      if (i == 7)
        sd = 1;
    
      else sd = i + 1;
    
      cout << sd;
      month++;
      j = 1;
      i = 0;
      line = 1; //infinite loop here!On removing line=1, it works fine except spaces.
    }
}