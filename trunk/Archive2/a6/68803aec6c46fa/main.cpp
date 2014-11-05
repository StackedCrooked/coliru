#include <iostream>

struct A
{
    A(){ std::cout << "A()" << std::endl; };
    A(A&){ std::cout << "A(A&)" << std::endl; };
    A(A&&){ std::cout << "A(A&&)" << std::endl; };
};

A foo(){
    return A();
}

A t(A()){ };
A d(foo());

A (*f)() = foo;

int main()
{ 
    t(f);
}

