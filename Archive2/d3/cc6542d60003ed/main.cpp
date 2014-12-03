#include <iostream>

struct A
{
    A(const A&){ std::cout << "A(const A&)" << std::endl; }
    A(){ std::cout << "A()" << std::endl; }
};

struct B
{
    B(){ std::cout << "B()" << std::endl; }
    operator A(){ return A(); }
};

B b;

void foo(A) { }

int main(){ foo(b); }