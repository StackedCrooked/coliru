#include <iostream>
 
using namespace std;
 
int main()
 
{
    int code;
 
    cout << "Enter Secret Code" << endl;
    cin >> code;
 
    if (code = 161821) 
    {
 
       cout << "Access Granted" << endl; 
       cout << "Proseed With Caution!" << endl;
 
 }
 
   else {
 
   cout << "Access Denied"<< code << endl;
   cout << code << " Error" << endl;
 
 }
 
   return 0;
}

