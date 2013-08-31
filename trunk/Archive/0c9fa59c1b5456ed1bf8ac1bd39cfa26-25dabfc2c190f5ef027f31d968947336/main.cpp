#include <initializer_list>
#include <iostream>

struct A
{
    A() { }
    A(std::initializer_list<A> l) { std::cout << "init-list" << std::endl; }
    A(A const& a) { std::cout << "copy-ctor" << std::endl; }
};

int main()
{
    A a(A{});
    A b{A()};
}
