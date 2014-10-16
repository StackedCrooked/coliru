#include <boost/variant.hpp>
#include <vector>
#include <iostream>

template <typename ...Args>
void foo(boost::variant<Args...> const & v)
{
    std::cout << v << '\n';
}

int main()
{
    boost::variant<int, double, bool> v(1.5f);
    foo(v);
}
