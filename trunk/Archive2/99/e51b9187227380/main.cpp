#include <iostream>
#include <climits>

struct A
{
    unsigned int a : 3;
};

A a{7};

decltype(a.a) foo()
{
    return a.a;
}

int main()
{
    std::cout << foo();
}