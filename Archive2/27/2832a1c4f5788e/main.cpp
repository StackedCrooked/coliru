#include <iostream>

struct A
{
    enum E { x = 2, y = 3 };
};

int x = A::x;

int main(){ std::cout << x << std::endl; }