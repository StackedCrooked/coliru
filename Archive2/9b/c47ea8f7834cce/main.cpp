#include <iostream>
#include <initializer_list>
#include <string>

struct X
{
    X(char const*, char const*)
    { std::cout << "X(char const*, char const*)" << std::endl; }
    
    X(std::initializer_list<std::string>) 
    { std::cout << "X::X(std::initializer_list<std::string>)" << std::endl; }
};

int main()
{
    X x{"Hello", "World"};
}