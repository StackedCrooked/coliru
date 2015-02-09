template <typename Tp>
struct variable_template {
  static constexpr Tp object = Tp{};
};

struct foo {
  template<typename Tp>
  constexpr int operator()(Tp&&) const {
    return 0;
  }
};

#include <cassert>
int main() {
  assert(variable_template<foo>::object(3) == 0);
  return 0;
}