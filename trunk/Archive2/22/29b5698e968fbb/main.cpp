#include <iostream>

class A
{
    static int a;
    friend void foo();
};

int A::a = 10;

friend void foo(){ std::cout << a << std::endl; }



int main(){ foo(); }