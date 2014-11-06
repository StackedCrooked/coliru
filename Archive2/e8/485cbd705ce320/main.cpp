#include <iostream>

struct A
{
    A(){ std::cout << "A()" << std::endl; };
    A(A&&){ std::cout << "A(A&&)" << std::endl; };
};

A t(A());

int main(){ }

