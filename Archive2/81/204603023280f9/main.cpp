#include <iostream>

template<class>
struct typeof;

template<class T>
void g(T&) { std::cout << __PRETTY_FUNCTION__ << std::endl; }

struct X
{
    void f() { g(&*this); }
};

int main()
{
    X().f();
}