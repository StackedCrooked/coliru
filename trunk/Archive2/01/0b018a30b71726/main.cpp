#include <iostream>
#include <limits>

struct A
{
    A(const A&){ std::cout << "~A()" << std::endl; }
};

union U
{
    A a;
};

U u;

int main()
{

}

