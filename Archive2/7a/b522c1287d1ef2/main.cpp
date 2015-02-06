#include <iostream>

template<class T>
void g(T&) { std::cout << __PRETTY_FUNCTION__ << std::endl; }

struct X
{
    X() { g(&*this); }
};

int main()
{
    X{};
}