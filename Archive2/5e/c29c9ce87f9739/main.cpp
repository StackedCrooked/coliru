#include <initializer_list>
#include <iostream>
#include <vector>

#include <cstdlib>

struct A
{

    A() = default;
    A(A const &) { std::cout << __PRETTY_FUNCTION__ << std::endl; }
    A(A &&) { std::cout << __PRETTY_FUNCTION__ << std::endl; }
    A & operator = (A const &) { std::cout << __PRETTY_FUNCTION__ << std::endl; return *this; }
    A & operator = (A &&) { std::cout << __PRETTY_FUNCTION__ << std::endl; return *this; }

};

int main()
{
    for (auto&& i : std::initializer_list<A> { A{}, A{}, A{} })
		std::cout << &i << '\n';
}
