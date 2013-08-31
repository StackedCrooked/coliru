#include <type_traits>

template<typename T>
struct foo {};

template<typename T>
constexpr std::true_type test(foo<T>);

constexpr std::false_type test(...);

template<typename T>
struct is_instantiation_of_foo : public decltype(test(std::declval<T>())) { };

template<typename FooType>
struct bar {
  static_assert(is_instantiation_of_foo<FooType>::value, "");
};

struct foo_sub : foo<int> {
};

int main(int,char**)
{
  bar<foo_sub> b;
  return 0;
}
