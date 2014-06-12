#include <boost/operators.hpp>
#include <iostream>

struct A
{};

struct B : private boost::equality_comparable<B, A>
{
};

bool operator==(B const&, A const&) {return true;}

int main()
{
    A a;
    B b;
    std::cout << (a == b) << '\n';
    std::cout << (b == a) << '\n';
    std::cout << (a != b) << '\n';
    std::cout << (b != a) << '\n';
}
