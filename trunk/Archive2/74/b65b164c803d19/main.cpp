#include <iostream>
#include <cmath>

namespace detail {
  template<class... Ts>
  constexpr int constexpr_check (Ts... args) {
    return sizeof...(args)+1 ? 0 : throw 1;
  }
}

template<bool>
constexpr int pow (int base, int exp) {
  return exp ? pow (base, exp-1) * base : 1;
}

template<>
int pow<false> (int base, int exp) {
  std::cout << "(not constexpr) ";
  return std::pow (base, exp);
}

#define constexpr_call(func, ...) (func <noexcept(detail::constexpr_check ( __VA_ARGS__ )) > (__VA_ARGS__))

int main () {
  {
    std::cout << constexpr_call (pow, 2, 8) << std::endl;
  }

  {
    constexpr int e = 4;
    std::cout << constexpr_call (pow, 2, e) << std::endl;
  }

  {
    int e = 4;
    std::cout << constexpr_call (pow, 2, e) << std::endl;
  }
}
