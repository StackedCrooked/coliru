#include <iostream>
#include <limits>

struct A
{
    A(){ std::cout << "A()" << std::endl; }
};

struct U
{
    A a;
};

U u;

int main()
{

}

