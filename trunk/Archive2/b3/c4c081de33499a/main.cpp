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
    A(const C&, const C&){ std::cout << "A(const C&, const C&)" <<std::endl; }
};

B b;
C c;
A a({b, b});


int main(){ }