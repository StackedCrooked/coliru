#include <type_traits>

constexpr int value(int p)
{
    return p;
}

template<class... TT>
constexpr int value(int val, int p0, TT... pp)
{
    return value(val*10 + p0, pp...);
}

template<char... Digits>
constexpr auto operator"" _c()
-> std::integral_constant<int, value(0, Digits - '0'...)>
{
    return {};
}


#include <iostream>

int main()
{
    std::cout << 42_c << "\n";
}