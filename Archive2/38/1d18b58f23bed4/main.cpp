#include <iostream>
#include <string>
#include <iostream>

using namespace std;

void main()
{
    int PIN[4] = {};
    string txtNr ="1st";
    for(int i=0;i<4;i++)
    {
      if(i=0)
        txtNr = "1st";
      if(i=1)
        txtNr = "2nd";
      if(i=2)
        txtNr = "3rd";
      if(i=3)
        txtNr = "4th";
      cout << "Please enter the " << txtNr <<" number: ";
      cin >> PIN[i];
    }


        for(int i=0;i<4;i++)
        {
           cout << PIN[i] << endl;
        }
}