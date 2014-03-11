#include <cstdint>

template <typename T>
constexpr T fib(T n) {
  return n < 2 ? 1 : fib(n - 1) + fib(n - 2);
}

constexpr auto max_fib_32 = fib(int32_t{45});
constexpr auto max_fib_64 = fib(int64_t{91});
constexpr auto max_fib_128 = fib(__int128{183});
