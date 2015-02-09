struct A { }; struct T { };

A foo() { return {}; }

int main()
{
    T x(A(z), A());
    
    x({}, foo);
}

#include <iostream>

T x(A, A())
{
    std::cout << "Mmpherg";
    return {};
}