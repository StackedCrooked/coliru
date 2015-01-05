#include <iostream>

struct A
{
    A(){ }
    void foo(){ std::cout << "foo()" << std::endl; }
    void foo() const{ std::cout << "foo() const" << std::endl; }
};

A aa;
const A a;
int main(){ aa.foo(); a.foo(); }