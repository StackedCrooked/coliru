#include <iostream>

int forward(int& i)
{
    std::cout << "lvalue: ";
    return i;   
}

int forward(int&& i)
{
    std::cout << "rvalue: ";
    return i;    
}

int main()
{
    int i = 1;
    
    std::cout << forward(0) << std::endl;
    std::cout << forward(i) << std::endl;
    return 0;
}