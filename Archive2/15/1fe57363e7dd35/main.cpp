#include <iostream>
using namespace std;

const int MAX_SIZE = 10;

void swapItems(int& first, int& second) // Swap two values by reference
{
    int tempVal;

    tempVal = first;
    first = second;
    second = tempVal;
}

void quickSort(int myArray[], int first, int last)
{

    int pivotIdx = (first + last) / 2; // middle of array

    int leftIdx = first;
    int rightIdx = last;

    while (leftIdx <= rightIdx)
    {
        if (myArray[leftIdx] > myArray[pivotIdx])
        {
            swapItems(myArray[leftIdx], myArray[pivotIdx]);
        }
        if (myArray[rightIdx] < myArray[pivotIdx])
        {
            swapItems(myArray[rightIdx], myArray[pivotIdx ]);
        }
        leftIdx++;
        rightIdx--;
    }

    for (int i = 0; i < MAX_SIZE; ++i)
        cout << myArray[i] << ' ';

    cout << endl;
}

int main() {
    { int myArray[MAX_SIZE] = {0, 7, 4, 1, 8, 5, 2, 9, 6, 3}; quickSort(myArray, 0, 9);}
    return 0;
}