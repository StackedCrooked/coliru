#include <iostream>
#include <array>
#include <algorithm>

using namespace std;

int main()
{
    int myArray[15];

    for (int i = 0; i <15; i++)
    {
        myArray[i] = 15 + rand() % (55 - 15 + 1);
    }

    for (int i = 0; i < 15; i++)
    {
        cout << myArray[i] << " ";
    }
    cout << endl;

    int lowIndex = 0;
    int highIndex = 0;

    cout << "Enter in a low index of the array (0-14): " << endl;
    cin >> lowIndex;
    cout << "Enter in a higher index of the array (0-14): " << endl;
    cin >> highIndex;

    cout << "The lowest number in the range of array indices is: ";
    cout << *std::min_element(myArray + lowIndex, myArray + highIndex) << endl;

    return 0;
}