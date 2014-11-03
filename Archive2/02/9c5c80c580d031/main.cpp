#include <iostream>

struct A
{
    A(){}
    A(const A&){ std::cout << "A(const A&)" << std::endl; }
    A(const A&&){ std::cout << "A(const A&&)" << std::endl; }
};

A baz()
{
    return A();
}

int main()
{ 
    A t = A();
    A f(baz());
    A d(t);
}

