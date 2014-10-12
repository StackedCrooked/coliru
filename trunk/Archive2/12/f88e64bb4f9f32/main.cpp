#include <iostream>
#include <stdexcept>

struct X
{
    X() { }
    ~X() { std::cout << "X::~X()" << std::endl; }
    X(int) : X{} { throw std::exception{}; }
};

struct Y
{
    Y() { throw std::exception{}; }
    ~Y() { std::cout << "Y::~Y()" << std::endl; }
    Y(int) : Y{} {  }
};

int main()
{
    try
    {
        X x{42};
    }
    catch (std::exception const&) { }
    
    try
    {
        Y y{42};
    }
    catch (std::exception const&) { }
}