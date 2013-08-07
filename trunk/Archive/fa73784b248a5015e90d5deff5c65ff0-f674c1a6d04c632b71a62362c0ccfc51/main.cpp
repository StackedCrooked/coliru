#include <iostream>
#include <string>
#include <vector>


int main()
{
    double arr[] = {
    0.0,    0.1, 0.2, 0.5,
    0.1,    0.2, 0.3, 0.4,
    0.2,    0.0, 0.1, 0.3
    };
    
    
    int numElements = sizeof(arr)/sizeof(arr[0]);

    std::cout << numElements;

   return 0;
}
