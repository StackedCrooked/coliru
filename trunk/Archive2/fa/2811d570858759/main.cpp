#include <iostream>

template <int n>
struct base { static constexpr int value = n; };

struct A : base<0> { };
struct B : base<1> { };
struct C : base<2> { };

struct D : A, B, C { };

template <int n>
static base<n> base_cast(base<n>);

template <typename T, typename B = decltype(base_cast(std::declval<T>()))>
static std::integral_constant<int, B::value> f(int);

template <typename T>
static std::integral_constant<int, -1> f(...);

constexpr int value = decltype(f<D>(0))::value;

int main()
{
    std::cout << value << std::endl;
}