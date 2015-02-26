#include <algorithm>    //copy
#include <iostream>     // cout
#include <iterator>     // iostream_iterator

void foo()
{
    int arr[] = { 1, 2, 3 };
    int* array = new int[3]; 
    std::copy(arr, arr + 3, array);
    std::copy(array, array + 3, std::ostream_iterator<int>(std::cout, ", "));

    // better hope nothing bad like and exception happens in between

    delete[] array;
}

int main() 
{    
    foo();
}