#include <iostream>
#include <cstdlib>
#include <cstddef>
using namespace std;

typedef int *IntArrayPtr;

void fill_array(int a[], int size)
{
    cout << "Enter" << size << "integers.\n";
    for (int index = 0; index < size; index++)
    {
        cin >> a[index];
    }
}
void sort(int a[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - 1; j++)
        {
            if (a[j] < a[j + 1])
            {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }

    }
    cout << "in ascending order the numbers are:";
    for (int index = 0; index < size; index++)
    {
        cout << a[index] << " ";
        cout << endl;
    }
}
void sortd(int arr[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = size - 1; j >= 0; j--)
        {
            if (arr[j + 1] > arr[j])
            {
                int temp = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = temp;
            }
        }
    }
    cout << "in descending order the numbers are:";
    for (int index = 0; index < size; index++)
    {
        cout << arr[index] << " ";
        cout << endl;
    }
}
int main()
{
    int input;
    cout << "to sort via forward sorting press 1, for backward sorting press 2";
    cin >> input;
    int array_size;

    IntArrayPtr a;
    a = new int[array_size];


    if (input == 1)
    {
        //int array_size;
        cout << "how many numbers will be sorted?";
        cin >> array_size;
        array_size = (sizeof(a) / sizeof(*a));
        fill_array(a, array_size);
        sort(a, array_size);
    }
    else if (input == 2)

    {
        int array_size1;
        cout << "how many numbers will be sorted?";
        cin >> array_size1;
        array_size1 = (sizeof(a) / sizeof(*a));
        fill_array(a, array_size1);
        sortd(a, array_size1);
    }
}