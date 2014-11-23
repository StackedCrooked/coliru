#include <iostream>

struct B{ };

struct A : B
{
    A(){ }
    A(const B&){ }
};

B b;
A a = b;


int main(){ }