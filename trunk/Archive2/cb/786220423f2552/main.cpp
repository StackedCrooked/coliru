#include <iostream>

struct A
{
    A()
    {
        std::cout << "A()" << std::endl;
    }
};

A a();

int main()
{
}