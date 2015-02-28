#include <iostream>

struct A
{
    int b = 3;
    int a = A::b;
};

A a;

int main() { std::cout << a.a << std::endl; }