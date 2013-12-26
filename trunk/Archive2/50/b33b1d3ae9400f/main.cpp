#include <initializer_list>
#include <iostream>

struct X
{
    X() { std::cout << "X()"; }
    X(std::initializer_list<int>) { std::cout << "X(init-list)"; }
};

int main()
{
    X x{};
}