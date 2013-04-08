#include <iostream>
#include <vector>

int main()
{
    int * arr = new int [0];
    
    arr[0] = 0;
    
    arr[1] = 2;
    
    std::cout  << arr << " " << *arr << " " << arr[0] << " " << arr[1];
}
