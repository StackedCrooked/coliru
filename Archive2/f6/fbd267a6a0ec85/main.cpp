#include <iostream>

struct A;

namespace B
{
    struct A
    {
        int a;
        A() : a(10){ }
        friend void foo(A* a);
    };
}

void foo(A* a)
{
    std::cout << a -> a << std::endl;
}

A* a = new A;

int main()
{
    foo(a);
}