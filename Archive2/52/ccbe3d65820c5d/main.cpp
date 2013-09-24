// Programer: Ben Robertson
// Class: CSC100
// Assignment: 5.1.5

#include <iostream>
#include <iomanip>

using namespace std;

int main()

{
    // This program will convert feet to meters.
    int foot; // from what unit of measure
    double meter; // to what unit of measure
    cout << "FEET   METERS" << endl; 
    cout << "----   ------\n" << endl; // Line to underline title words
    cout << setprecision(2) << setiosflags(ios::showpoint) << setiosflags(ios::fixed); // used to make the numbers appear nice
    
    foot = 3; // starts at 3
    while (foot <= 30) // while 3 feet or more or equal to 30
    
    {
        meter = 0.305 * foot; // formula used to convert feet to meters
        cout << setw(3) << foot << "     "; //  3 feet to
        cout << setw(3) << meter <<  " " << endl; // feet times 3.28
        
        foot = foot + 3; // foot increases by 3
    }
    
    return 0; // stop all programming
}
