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

int forward(int*&& ptr_i)
{
    std::cout << "rvalue ptr: ";
    return *ptr_i;   
}

int forward(int*& ptr_i)
{
    std::cout << "lvalue ptr: ";
    return *ptr_i;   
}

int main()
{
    int i = 1;
    
    
    int* ptr_i = &i;
    
    std::cout << forward(0) << std::endl;
    std::cout << forward(i) << std::endl;
    std::cout << forward(ptr_i) << std::endl;
    std::cout << forward(&i) << std::endl;
    return 0;
}