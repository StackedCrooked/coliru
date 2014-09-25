#include <iostream>
#include <initializer_list>

struct X
{
    X() 
    { std::cout << "X::X()" << std::endl; }
    
    X(std::initializer_list<int>) 
    { std::cout << "X::X(std::initializer_list<int>)" << std::endl; }
};

int main()
{
    X x1;
    X x2{};
    X x3 = {};
}