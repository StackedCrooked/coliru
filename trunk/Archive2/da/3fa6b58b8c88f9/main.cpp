#include <boost/variant.hpp>
#include <vector>
#include <iostream>

template <typename ...Args>
void foo(std::vector<boost::variant<Args...> > const & v)
{
    std::cout << v.size() << '\n';
}

int main()
{
    using V = boost::variant<int, double, bool>;
    V v(1.5f);
    foo(std::vector<V> {v, v});
}
