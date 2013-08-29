#include <type_traits>

template<template<typename...> class TT, typename... Ts>
struct is_instantiation_of : public std::false_type { };

template<template<typename...> class TT, typename... Ts>
struct is_instantiation_of<TT, TT<Ts...>> : public std::true_type { };

template<typename T>
struct foo {};
 
template<typename T>
using foo_alt = foo<T>;
 
template<typename FooType>
struct bar {
  static_assert(is_instantiation_of<foo,FooType>::value, "failure");     //success
  static_assert(is_instantiation_of<foo_alt,FooType>::value, "failure"); //fail
};
 
int main(int argc, const char * argv[])
{
  bar<foo_alt<int>> b;
  return 0;
}