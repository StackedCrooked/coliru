#include <iostream>

struct B
{
};

struct C : B
{
};

int main()
{
    B b;
    b.C::~B();
}