#include <iostream>

void foo(double d = 0)
{
    std::cout << "double" << std::endl;
}

void foo(int i)
{
    std::cout << "int" << std::endl;
}

void foo(char c)
{
    std::cout << "char" << std::endl;
}

int main()
{
    foo();
    foo(0.0);
    foo(3);
    foo(char(4));
    
    return 0;
}