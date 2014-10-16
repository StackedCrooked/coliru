#include <boost/variant.hpp>
#include <vector>
#include <iostream>

template<typename T>
struct stuff {};

template<typename T>
void foo(std::vector<stuff<T> > const & v)
{
    std::cout << v.size() << '\n';
}

int main()
{
    std::vector<stuff<int> > x;
    stuff<int> c;
    x.push_back(c);
    x.push_back(c);
    foo(x);
}
