#include <iostream>

void foo();

class A
{
    friend void foo(){ std::cout << a << std::endl; }
    static int a;
};

int A::a = 10;

int main(){ foo(); }