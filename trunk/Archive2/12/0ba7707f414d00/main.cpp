#include <iostream>

struct A 
{
    A(){ };
    ~A() = delete; //{ std::cout << "~A::A()" << std::endl; };
};

struct B: A { };

B *b = new B;

int main()
{
}