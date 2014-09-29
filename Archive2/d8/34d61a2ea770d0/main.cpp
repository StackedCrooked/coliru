#include <iostream>

using namespace std;

int SIZE;

void printArray(const int * a)
{
    for (int i = 0; i < SIZE; ++i)
    {
        cout << " " << a[i];       
    }
    cout << endl << "SIZE = " << SIZE << endl;

}

void insert(int* &arr, int element, int index) // <<< make `arr` a reference so that we can modify it
{
    if (index < SIZE)
    {
        arr[index] = element;
    }
    else
    {
        int* new_array = new int[SIZE + 1];
        for (int i = 0; i < SIZE; i++)
        {
            new_array[i] = arr[i];
        }
        new_array[SIZE] = element;
        SIZE++;
        delete [] arr;    // <<< delete old `arr`
        arr = new_array;  // <<< replace it with `new_array`
    }
}

int main()
{
    SIZE = 5;
    int *a = new int[SIZE];
    for (int i = 0; i < SIZE; ++i)
    {
        a[i] = i;   
    }
    printArray(a);
    insert(a, 42, 2);
    printArray(a);
    insert(a, 43, 5);
    printArray(a);
    return 0;
}
