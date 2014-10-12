#include <iostream>


struct A 
{
    int a;
    A();
    ~A();
};

A::~A()
{
    std::cout << "~A()" << std::endl; 
}

A::A()
{
    std::cout << "A()" << std::endl; 
} 



int main()
{
    A b = A();
    std::cout << "side effect" << std::endl;
}