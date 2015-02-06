#include <iostream>
#include <utility>
#include <tuple>

template<typename T> void foo(int, double, char, bool) { std::cout << __PRETTY_FUNCTION__ << "\n"; }
template<typename T> void foo(int, double, char, short) { std::cout << __PRETTY_FUNCTION__ << "\n"; }

template<typename R, typename... Args>
using func_t = R(Args...);

template<typename, typename>
struct helper;

template<typename T, typename... Args>
struct helper<T, std::tuple<Args...>>
{
    using return_t = decltype(foo<T>(std::declval<Args>()...));
    using fptr_t = func_t<return_t, Args...>*;
    constexpr static fptr_t static_member = foo<T>;
};

template<typename T, typename... Args>
typename helper<T, std::tuple<Args...>>::fptr_t const helper<T, std::tuple<Args...>>::static_member;

using tuple0 = std::tuple<int, double, char, bool>;
using tuple1 = std::tuple<int, double, char, short>;

template struct helper<int, tuple0>;
template struct helper<double, tuple0>;
template struct helper<int, tuple1>;

int main()
{}