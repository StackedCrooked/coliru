#include <iostream>
#include <string>
#include <vector>

struct A
{
    virtual void f(int) {}
};

struct B
{
    virtual void f(int*) {}
};

int main()
{
    B b;
    int a = 10;

    b.f(a);
}
