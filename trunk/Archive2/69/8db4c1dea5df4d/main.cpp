namespace detail {
  template<class... Ts> constexpr int constexpr_check (Ts...) { return 1; }
}

#define CONDITIONALLY_INVOKE_CONSTEXPR(FUNC, ...) \
  (FUNC <noexcept(detail::constexpr_check(__VA_ARGS__))>(__VA_ARGS__))

// -----------------------------------------------------------------------------

#include <iostream>
#include <cmath>

template<bool B = false>
constexpr int pow (int base, int exp) {
  return exp ? pow<B> (base, exp-1) * base : 1;
}

template<>
int pow<false> (int base, int exp) {
  std::cout << "(not constexpr) ";
  return std::pow (base, exp);
}

int main () {
  {
    constexpr int e = 4;
    constexpr int r = CONDITIONALLY_INVOKE_CONSTEXPR (pow, 2, e);
    std::cout  << r << std::endl;
  }
  {
    constexpr int r = CONDITIONALLY_INVOKE_CONSTEXPR (pow, 2, 4);
    std::cout  << r << std::endl;
  }
  {
    int e = 4;
    int r = CONDITIONALLY_INVOKE_CONSTEXPR (pow, 2, e);
    std::cout << r << std::endl;
  }
}