#include <iostream>

struct B
{
    operator int()
    {
        return int();
    }
};

struct A
{
    A(int, int){ std::cout << "A(int, int)" << std::endl; }
};

A a({B(), B()});

int main()
{ 
}