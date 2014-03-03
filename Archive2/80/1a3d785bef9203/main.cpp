#include <iostream>

int main()
{
    { 
        int * yolomode{new int{10}}; //allocate on heap
        std::cout << *yolomode << std::endl;  
    } 
    
    *yolomode++; 
    std::cout << *yolomode << std::endl;
    delete yolomode;
}