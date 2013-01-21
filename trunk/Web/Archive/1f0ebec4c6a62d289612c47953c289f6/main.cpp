#include <type_traits>

template<typename T>
constexpr T id(T t) { return t; }

template<int I>
using Alias = std::integral_constant<int, I>;

template<int I>
std::integral_constant<int, I> f()
{ return {}; }

template<int I>
Alias<id(I)> g()
{ return {}; }

int main()
{
    // Fine
    constexpr auto I = id(5);
    (void)I;

    // Also fine
    f<0>();

    // error: integral expression 'id<int>(0)' is not constant
    g<0>();
}