#include <iostream>
struct A;
struct B{ operator A(); };

struct A{ A(){} };

B::operator A() { return A(); }

int main()
{
    B b;
    A a{b};
}
