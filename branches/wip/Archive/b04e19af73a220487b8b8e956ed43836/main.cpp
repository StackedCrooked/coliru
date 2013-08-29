#include <type_traits>

template<class T> struct X;
template<> struct X<int>{ void f(){} };

template<class T>
auto test(int) -> decltype(void(&T::f), std::true_type{});
template<class>
auto test(long) -> std::false_type;

int main(){
  static_assert(decltype(test<X<void>>(0))::value == false, "X<void>");
  static_assert(decltype(test<X<int>>(0))::value == true, "X<int>");
}