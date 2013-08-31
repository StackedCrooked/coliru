#include <cstddef>

namespace detail {
using std::size_t;

constexpr size_t mid(size_t low, size_t high) {
  return low + (high - low) / 2;
}

// precondition: low*low <= n, high*high > n.
constexpr size_t ceilsqrt(size_t n, size_t low, size_t high) {
  return low + 1 >= high
    ? high
    : (mid(low, high) * mid(low, high) == n)
      ? mid(low, high)
      : (mid(low, high) * mid(low, high) <  n)
        ? ceilsqrt(n, mid(low, high), high)
        : ceilsqrt(n, low, mid(low, high));
}

constexpr size_t ceilsqrt(size_t n) {
  return ceilsqrt(n, 1, size_t(1) << 32);
}

// return true if n is divisible by an odd integer in
// [2 * low + 1, 2 * high + 1).
constexpr bool find_factor(size_t n, size_t low, size_t high)
{
  return low + 1 >= high
    ? ((n % (2 * low + 1)) == 0 ? true : false)
    : (find_factor(n, low, low + (high - low) / 2)
       || find_factor(n, low + (high - low) / 2, high));
}
}

constexpr bool is_prime(std::size_t n)
{
  using detail::find_factor;
  using detail::ceilsqrt;

  return n > 1
    && (n == 2
        || (n % 2 == 1
            && (n == 3
                || !find_factor(n, 1, (ceilsqrt(n) + 1) / 2))));
}

#include <iostream>

int main() {
  static_assert(is_prime(100000007),  "100000007 is a prime!");
  static_assert(is_prime(1000000007), "1000000007 is a prime!");
  static_assert(is_prime(1000000009), "1000000009 is a prime!");
  static_assert(!is_prime(1000000011), "1000000011 is not a prime!");
  static_assert(is_prime(1000000000039), "1000000000039 is a prime.!");
}
