#include <type_traits>

template<typename T>
struct foo {};

template<typename T>
struct is_instantiation_of_foo : std::false_type { };

template<typename...Ts>
struct is_instantiation_of_foo<foo<Ts...>> : std::true_type { };


template<typename FooType>
struct bar {
  static_assert(is_instantiation_of_foo<FooType>::value, ""); //fail
};

template<typename T>
using foo_alt = foo<T>;

int main(int,char**) {
  //both of these fail:
  bar<foo<int>> b;
  bar<foo_alt<int>> b2;

  return 0;
}
