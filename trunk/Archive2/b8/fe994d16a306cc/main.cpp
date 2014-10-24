#include <type_traits>
#include <limits>

template <typename T, T v>
using iconst = std::integral_constant<T, v>;

template <typename B, typename A>
constexpr B convert( A a )
{
    using aMax = iconst<A, std::numeric_limits< A >::max()>;
    using bMax = iconst<B, std::numeric_limits< B >::max()>;
    return a * (bMax::value / aMax::value);
}

#include <iostream>

int main()
{
    constexpr auto i = convert<long>(4);
    std::cout << i;
}