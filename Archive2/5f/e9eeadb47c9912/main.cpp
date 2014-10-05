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

    int lowIndex = 2;
    int highIndex = 7;


    cout << "The lowest number in the range of array indices is: ";
    cout << *std::min_element(myArray + lowIndex, myArray + highIndex) << endl;

    return 0;
}