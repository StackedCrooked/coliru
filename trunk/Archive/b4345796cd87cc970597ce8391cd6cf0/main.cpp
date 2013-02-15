#include <iostream>
#include <thread>

int main()
{
    int i = -2147483648;
    std::cout << sizeof(i);
    std::cout << "\n";
    std::cout << (i / -1 );
    
}