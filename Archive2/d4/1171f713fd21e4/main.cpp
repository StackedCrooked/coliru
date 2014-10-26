#include <iostream>
#include <limits>

struct A
{
    A(){ std::cout << "A()" << std::endl; }
};

union U
{
    A a;
};

U u;

int main()
{

}

