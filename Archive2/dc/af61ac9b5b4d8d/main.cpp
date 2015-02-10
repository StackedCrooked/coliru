template <typename Tp>
struct variable_template {
  static constexpr Tp value = Tp{};
};

template <typename Tp>                     // <- comment me
constexpr Tp variable_template<Tp>::value; // <- comment me

struct foo {
  int bar() const { return 0; }
};

#include <memory>
int main() {
  std::addressof(variable_template<foo>::value);
  variable_template<foo>::value.bar();
  return 0;
}