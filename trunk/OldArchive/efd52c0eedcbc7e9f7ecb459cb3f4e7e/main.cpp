#include <iostream>

void f(){}

int main()
{
    std::cout << (long)&f << std::endl;
}