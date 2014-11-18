#include <iostream>

struct A 
{
    A(){ };
    ~A(){ std::cout << "~A::A()" << std::endl; };
};

struct B: A { };

B *b = new B;

int main()
{
}