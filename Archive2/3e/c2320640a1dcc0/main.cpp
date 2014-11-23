#include <iostream>

struct B
{ 
    B(){ std::cout << "B()" << std::endl; }
};

struct A : B
{
    A(){ std::cout << "A()" << std::endl; }
    A(const B&){ std::cout << "A(const B&)" << std::endl;}
};

B b;
A a = b;


int main(){ }