#include <iostream>

struct B
{
    int i;
};    

struct A
{
    const struct B b;
    A() = default;
};

int main()
{
    A a;
}