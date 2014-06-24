#include <iostream>
#include <type_traits>
#include <cstdint>

auto f = [](auto x){return x*2;};

template < typename X, typename=decltype(f(std::declval<X>())) >
std::true_type test_impl(int);

template < typename >
std::false_type test_impl(...);

template < typename T >
using test = decltype(test_impl<T>(0));

struct A{};

int main()
{
   static_assert(not test<A>{},"");
   return 0;
}