#include <iostream>
#include <limits>

struct A
{ 
    ~A(){ };
};

A::A(){ };

int main()
{
    A a;
}

