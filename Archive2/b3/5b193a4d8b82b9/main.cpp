#include <cstdio>

static constexpr struct {
  template<typename...Args>
  auto operator()(Args&&...args) const { return 123; }
} u;

static const auto v = [](auto&&...) { return 123; };

int main() {
  printf("%d\n", u());
  // printf("%d\n", v()); // error
}
