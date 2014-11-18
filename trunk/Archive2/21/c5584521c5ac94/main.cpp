#include <iostream>

struct A 
{
    A(int x){ };
    ~A() = delete;
};

struct B : A
{
    B(int x) : A(x) {};
    ~B() = delete;
};

B *b = new B(3);

int main() {}
