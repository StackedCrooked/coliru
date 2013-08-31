#include <type_traits>
#include <iostream>

template <typename T, T value>
inline constexpr std::integral_constant<T, !value>
operator ! (std::integral_constant<T, value>)
{ return {}; }

int i = 5;
std::integral_constant<bool, true> a;

int main()
{
    auto x = !a;
    std::cout << std::is_same<decltype(x), bool>{};
}
