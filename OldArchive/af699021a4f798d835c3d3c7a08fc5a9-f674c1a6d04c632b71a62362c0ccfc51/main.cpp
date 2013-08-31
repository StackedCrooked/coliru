#include <cstddef>

using std::size_t;

// precondition: low*low <= n, high*high > n.
constexpr size_t ceilsqrt(size_t n, size_t low, size_t high) {
#define MID (low + (high - low) / 2)
  return low + 1 >= high ? high :
    (MID*MID == n) ? MID :
    (MID*MID <  n) ? ceilsqrt(n, MID, high) : ceilsqrt(n, low, MID);
#undef MID
}

constexpr size_t ceilsqrt(size_t n) {
  return n < 3 ? n : ceilsqrt(n, 1, (n + 1) / 2);
}

// return true if number is divisible by an odd integer in
// [2 * low + 1, 2 * high + 1).
constexpr bool scaled_has_factor(size_t number, size_t low, size_t high)
{
  return (low + 1 >= high ? ((number % (2 * low + 1)) == 0 ? true : false)
            : (scaled_has_factor(number, low, low + (high - low) / 2) ||
               scaled_has_factor(number, low + (high - low) / 2, high)));
}

constexpr bool is_prime(size_t number)
{
  return number > 1 &&
    (number == 2 ||
      (number % 2 == 1 &&
       (number == 3 || !scaled_has_factor(number, 1, (ceilsqrt(number) + 1) / 2))));
}

int main() {
  static_assert(is_prime(100000007ULL), ".1.");
  static_assert(!is_prime(100000009ULL), ".2.");
  static_assert(is_prime(1000000000039ULL), ".3.");
}
