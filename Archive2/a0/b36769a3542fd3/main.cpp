#include <iostream>
using namespace std;

void subfunction(string word)
{
    cout << word << endl;
}

int main()
{
    cout << "Enter a number: "; // ask user for a number
    int x;
    cin >> x; // read number from console and store it in x
    cout << "You entered " << x << endl;
    cout << "\n" << "Enter 'a': ";
    string y;
    cin >> y;
    if (y=="a"){
       cout << "You typed 'a'!!!";
       int z;
       cin >> z;
       return 0;
    }
    else {
         cout << "You didn't type 'a'!!!" << endl;
    }
    string word;
    subfunction("abc");
    
    return 0;
}