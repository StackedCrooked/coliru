#include <iostream>

class A
{
    friend void foo(){ std::cout << a << std::endl; }
    static int a;
};

void foo();

int A::a = 10;

int main(){ foo(); }