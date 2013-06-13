#include <iostream>


int main()
{
    const int ci = 1234;
    ++(int&)ci;
    std::cout << ci << std::endl;
    
    const int& cref = 1234;
    ++(int&)cref;
    std::cout << cref << std::endl;
    
    int&& rref = 1234;
    ++rref;
    std::cout << rref << std::endl;
}