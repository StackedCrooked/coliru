#include <iostream>
#include <typeinfo>
#include <string>
#include <cxxabi.h>

template<template<typename...> class TT, class T, size_t n, class... U>
struct insert;

template<template<typename...> class TT, class T, class U1, class... U>
struct insert <TT, T, 0, U1, U...>
{
  using type = TT<T, U1, U...>;
};

template<template<typename...> class TT, class T>
struct insert <TT, T, 0>
{
  using type = TT<T>;
};

template<template<typename...> class TT, class T, size_t n, class U1, class... U>
struct insert<TT, T, n, U1, U...>
{
  template <typename... X> using templ = TT<U1, X...>;
  using type = typename insert<templ, T, n-1, U...>::type;
};

template <typename t1, typename t2, typename t3, typename t4>
struct test {};

using result = insert<test, int, 2, double, char, void*>::type;

int main()
{
    std::string s = typeid(result).name();
    int status;
    s = abi::__cxa_demangle(s.c_str(), NULL, NULL, &status);
    std::cout << s << std::endl;
}
