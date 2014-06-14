#include <boost/operators.hpp>
#include <iostream>

struct A
{};

struct B : private boost::equality_comparable<B, A>
{
};

struct C : private boost::equality_comparable<C, A>,
           private boost::equality_comparable<C, B>
{
};

bool operator==(B const&, A const&) {return true;}
bool operator==(C const&, A const&) {return true;}
bool operator==(C const&, B const&) {return false;}

int main()
{
    A a;
    B b;
    std::cout << (a == b) << '\n';
    std::cout << (b == a) << '\n';
    std::cout << (a != b) << '\n';
    std::cout << (b != a) << '\n';
    std::cout << "------" << '\n';
    
    C c;
    std::cout << (a == c) << '\n';
    std::cout << (c == a) << '\n';
    std::cout << (a != c) << '\n';
    std::cout << (c != a) << '\n';
    std::cout << "------" << '\n';
    
    std::cout << (b == c) << '\n';
    std::cout << (c == b) << '\n';
    std::cout << (b != c) << '\n';
    std::cout << (c != b) << '\n';
    std::cout << "------" << '\n';
}
