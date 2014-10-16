#include <boost/variant.hpp>
#include <vector>
#include <iostream>

template <typename ...Args>
void foo(std::vector<boost::variant<Args...>> const & v)
{
    for (auto const & x : v) std::cout << x << '\n';
}

int main()
{
    boost::variant<int, double, bool> v(1.5f);
    foo(std::vector<boost::variant<int, double, bool>>{v, v, v});
}
