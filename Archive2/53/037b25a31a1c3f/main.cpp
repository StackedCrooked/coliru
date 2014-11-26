#include <iostream>

struct B;

struct C
{
    C(){ }
    C(const B&){ }
};

struct B
{ 
    B(){ }
    B(const C&){ }
};

struct A
{
    A(const C&, const C&){ }
};

B b;
C c;
A a({b, b});


int main(){ }