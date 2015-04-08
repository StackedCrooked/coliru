#include <iostream>
using namespace std;
int main()
{
    int number; // Variable to hold the last input integer
    int product = 1; // Variable to hold product of all inputs
    int count = 0; // Variable to hold amount of valid input integers not equal to 0

    do
    {
        cout << "Enter an integer number to be included in the product" << endl << "or enter 0 to end input: ";
        cin >> number; // Ask user to enter integers to be calculated

        if (number != 0) // If the input does not equal 0, it will be calculated in the product
        {
            product = product * number;
            count++;
        }
    }
    while (number != 0); // The loop will run until the user inputs a 0 value for number variable.

    if (count < 0) // If the user has entered 1 or more inputs for number variable that are not equal to 0, the program will display the product.
    {
        cout << endl << "The product is " << product << "." << endl;
    }

    return 0;
}