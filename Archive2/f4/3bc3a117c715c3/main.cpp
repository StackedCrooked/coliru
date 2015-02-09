template <typename Tp>
struct variable_template {
  static constexpr Tp object = Tp{};
};

struct foo {
  int i = 0;
  constexpr foo(): i{1} {}
  explicit constexpr foo(int a): i{a} {}
  template<typename Tp>
  constexpr int operator()(Tp&&) const {
    return 0;
  }
};

#include <iostream>
int main() {
  std::cout << variable_template<foo>::object.i << std::endl;
  //std::cout << std::addressof(variable_template<foo>::object.i) << std::endl;
  return 0;
}