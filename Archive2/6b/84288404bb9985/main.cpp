#include <iostream>
using namespace std;

void sortDescending(int[], int);
void shiftRight(int[], int);

int main()
{
    int length = 0;
    int* a;
    cout << "How many numbers would you like to sort?\n";
    cin >> length;
    a = new int[length];
    
    for (int i = 0; i < length; ++i)
    {
        cout << "Enter a number.\n";
        cin >> a[i];
    }
    
    sortDescending(a, length);
    std::cout << "After sortDescending(): ";
    
    for (int i = 0; i < length; ++i)
    {
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;
    
    shiftRight(a, length);
    std::cout << "After shiftRight(): ";
    
    for (int i = 0; i < length; ++i)
    {
        std::cout << a[i] << " ";
    }
    
    return 0;
}

void sortDescending(int a[], int length) //Sorts the numbers in the array in descending order.
{
    for (int i = 0; i < length; i++)
    {
        for (int k = 0; k < length; ++k)
        {
            if (a[i] < a[k])
            {
                int hold = a[i];
                a[k] = a[i];
                a[i] = hold;
            }
        }
    }
}

void shiftRight(int a[], int length)
{
    for (int i = 0; i < length; i++)
    {
        //a[length - i] = a[length - (i-1)]; // Not sure what this code is supposed to do. It actually cases undefined behavior!
    }
}