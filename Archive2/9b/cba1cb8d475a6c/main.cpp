
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

namespace detail {

  template<typename T>
  constexpr size_t bits(T = T()) {
    return sizeof(T) * 8;
  }

  template<typename T>
  constexpr T rotate(T x, uint8_t c) {
    c &= bits(x) - 1;
    return (x << c) | (x >> (bits(x) - c));
  }

  template<typename T>
  constexpr T check() {
    T r = 0;
    for(size_t i = 0; i <= (size_t(1) << bits<T>()) - 1; ++i) {
      for(size_t j = 0; j <= (size_t(1) << bits<uint8_t>()) - 1; ++j) {
        r += rotate(static_cast<T>(i), static_cast<unsigned>(j));
      }
    }
    return r;
  }

  template<typename T, T = check<T>()>
  constexpr bool verify(T *) {
    return true;
  }

  constexpr bool verify(...) {
    return false;
  }

  template<typename T>
  constexpr bool verify() { return verify(static_cast<T*>(nullptr)); }

}

template<typename T>
constexpr T rotate(T x, uint8_t c) {
  static_assert(detail::verify<T>(), "Cannot prove that this function is well-defined everywhere");
  return detail::rotate(x, c);
}
  

int main(int argc, char **argv) {
  printf("%d\n", rotate(static_cast<uint8_t>(argc), 1));
  return 0;
}

