#include <cstdint>

template <typename T>
constexpr T fib(T n) {
  return n < 2 ? 1 : fib(n - 1) + fib(n - 2);
}

constexpr auto fib_45 = fib(int32_t{45});
constexpr auto fib_46 = fib(int32_t{46});
constexpr auto fib_91 = fib(int64_t{91});
constexpr auto fib_92 = fib(int64_t{92});
constexpr auto fib_183 = fib(__int128{183});
constexpr auto fib_184 = fib(__int128{184});
