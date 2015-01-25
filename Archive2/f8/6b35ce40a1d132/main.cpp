#include <iostream>

struct A
{
//    A(A&&){ std::cout << "A(A&&)" << std::endl; }
//    A(A&){ std::cout << "A(A&)" << std::endl; }
    operator int(){ return 42; }
};

struct B
{
    operator A(){ return A(); }
};

B b;
int a = A(b);

int main(){ std::cout << a << std::endl; }