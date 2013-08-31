#include <iostream>
 using namespace std;

class Largest
{
public:
void findLargest(); // function to find largest number
};

void Largest::findLargest()
{
int counter = 0; // counter
int number; // input
int largest; // largest number

cout << "Enter the first number: ";
cin >> largest;

while ( ++counter < 10 )
{
cout << "Enter the next number : ";
cin >> number;

if ( number > largest )
largest = number;
} // end while

cout << "Largest is " << largest << endl;
}


