#include <iostream>
#include <initializer_list>

struct X
{
    X(std::initializer_list<int>) 
    { std::cout << "X::X(std::initializer_list<int>)" << std::endl; }
};

int main()
{
    X x2{};
    X x3 = {};
}