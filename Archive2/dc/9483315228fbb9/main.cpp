#include <iostream>

struct A
{
    A(const A&){ std::cout << "A(const A&)" << std::endl; }
    A(){ std::cout << "A()" << std::endl; }
};

struct B
{
    B(){ std::cout << "B()" << std::endl; }
    operator A(){ std::cout << "operator A()" << std::endl; return A(); }
};

const B b;

void foo(A) { }

int main(){ std::cout << "main function starting..." << std::endl; foo(b); }