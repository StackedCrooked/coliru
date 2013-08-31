#include <type_traits>

template<typename T>
struct foo {
    virtual void hello() = 0;
};

template<typename T>
constexpr std::true_type test(foo<T> const&);

constexpr std::false_type test(...);

template<typename T>
struct is_instantiation_of_foo : public decltype(test(std::declval<T>())) { };

template<typename FooType>
struct bar {
  static_assert(is_instantiation_of_foo<FooType>::value, "");
};

struct foo_sub : foo<int> {
    void hello() override { }
};

int main(int,char**)
{
  bar<foo_sub> b;
  return 0;
}
