#include <iostream>

struct C{ };

struct B
{ 
    B(){ }
    B(const C&){ }
};

struct A
{
    A(const C&, const C&){ }
    A(const B&){ }
};

B b;
C c;
A a(c, b);


int main(){ }