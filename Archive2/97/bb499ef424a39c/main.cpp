#include <type_traits>

constexpr int constexpr_check(...) { return 1; }

#define IS_CONSTEXPR_ARGLIST(...) \
    noexcept(constexpr_check(__VA_ARGS__))

#define IS_CONSTEXPR_TAG(...) \
    std::integral_constant<bool, IS_CONSTEXPR_ARGLIST(__VA_ARGS__)>{}

#define CONSTEXPR_DISPATCH(F, ...) \
    F(IS_CONSTEXPR_TAG(__VA_ARGS__), __VA_ARGS__)

constexpr int foo(std::true_type, int x, int y)
{
    return (x * y);
}

int foo(std::false_type, int x, int y)
{
    return (x + y);
}

#include <iostream>

int main()
{
    std::cout << CONSTEXPR_DISPATCH(foo, 0, 42) << std::endl;

    int x = 0;
    std::cout << CONSTEXPR_DISPATCH(foo, x, 42) << std::endl;
}