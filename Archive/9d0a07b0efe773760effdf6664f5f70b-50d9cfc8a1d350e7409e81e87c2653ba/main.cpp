#include <iostream>
#include <typeinfo>

struct A
{
    virtual ~A() {}
};

struct B : A {};


int main()
{
    std::cout << typeid(A).name() << std::endl;
    std::cout << typeid(B).name() << std::endl;
    
    B b;
    A & a = b;
    std::cout << typeid(a).name() << std::endl;
    std::cout << typeid(b).name() << std::endl;
}//a