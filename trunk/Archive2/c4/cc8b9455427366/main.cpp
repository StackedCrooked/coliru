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
    A(int){ std::cout << "A(int, int)" << std::endl; }
};

A a({B(), B()});
A b({B()}); //ill-formed
int main()
{ 
}