#include <iostream>
#include <stdexcept>

struct X
{
    X() { }
    ~X() { std::cout << "X::~X()" << std::endl; }
    X(int) : X{} { throw std::exception{}; }
};

int main()
{
    try
    {
        X x{42};
    }
    catch (std::exception const&) { }
}