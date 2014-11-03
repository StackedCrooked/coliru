#include <iostream>

struct A
{
    A(){}
    A(const A&){ std::cout << "A(const A&)" << std::endl; }
    A(const A&&){ std::cout << "A(const A&&)" << std::endl; }
};

void foo(A&)
{
    std::cout << "A&" << std::endl;
}

void foo(A&&)
{
    std::cout << "A&&" << std::endl;
}

A bar()
{
    return A();
}

int main()
{ 
    A t = A();
    foo(bar());
    foo(A());
    foo(t);
}

