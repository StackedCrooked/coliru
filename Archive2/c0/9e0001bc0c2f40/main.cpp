#include <boost/fusion/include/for_each.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/mpl/identity.hpp>

struct X{ X() = delete; static constexpr int value = 42; };

#include <iostream>

int main()
{
    using namespace boost;
    fusion::vector<mpl::identity<X>, mpl::identity<X>> v;
    fusion::for_each(v, [](auto x){ std::cout << decltype(x)::type::value << "\n"; });
}