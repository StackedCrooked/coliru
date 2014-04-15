#include <iostream>

using namespace std;


double average(double* a, int size)

{
    double total = 0;
    double* p = a;
    // p starts at the beginning of the array
    for (int i = 0; i < size; i++)
    {
        total = total + *p;
        // Add the value to which p points
        p++;
        // Advance p to the next array element
    }
    return total / size;
}

int main()
{
    double array[5] = {1,2,3,4,5};
    std::cout << average(array, 5);
}