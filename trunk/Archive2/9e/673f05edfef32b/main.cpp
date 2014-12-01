#include <cstdio>
#include <type_traits>

template<template<class...>class X>
struct defer {};

template<class, class...> struct apply {};
template<template<class...>class X, class...Ts>
struct apply< defer<X>, Ts... > {
    typedef X<Ts...> type;
};

template<typename E>
typename apply< typename std::enable_if<std::is_enum<E>::value,defer<std::underlying_type>>::type, E >::type::type
to_integral(E e) {
  return static_cast<typename std::underlying_type<E>::type>(std::move(e));
}
template<typename E>
typename std::enable_if<!std::is_enum<E>::value&&std::is_integral<E>::value,E>::type
to_integral(E e) {
  return std::move(e);
}

enum class MyEnum : int { A = 5 };

int main()
{
  auto a = to_integral(42);
  auto b = to_integral(MyEnum::A);
  printf("%d\n", a);
  printf("%d\n", b);
}