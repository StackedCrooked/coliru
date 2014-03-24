#include <type_traits>
#include <iterator>
#include <iostream>
#include <vector>

template<class T>
struct foo_trait {
  template<class U, class = decltype (std::begin (std::declval<U> ()), std::end (std::declval<U> ()))>
  static std::true_type  test (int);

  template<class>
  static std::false_type test (...);

  static constexpr bool value = decltype (test<T> (0))::value;
};

int
main (int argc, char *argv[])
{
  std::cerr << foo_trait<std::vector<int>>::value << "\n";
  std::cerr << foo_trait<             int>::value << "\n";
}