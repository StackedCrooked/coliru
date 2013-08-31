#include <cstddef>

using std::size_t;

constexpr bool scaled_has_factor(size_t number, size_t low, size_t high)
{
  return (low + 1 >= high ? (number % (2 * low + 1) == 0 ? true : false)
            : (scaled_has_factor(number, low, low + (high - low) / 2) ||
               scaled_has_factor(number, low + (high - low) / 2, high)));
}

constexpr bool is_prime(size_t number)
{
  return number > 1 &&
    (number == 2 ||
      (number % 2 == 1 &&
        (number == 3 || !scaled_has_factor(number, 1, (number + 3) / 4))));
}

#include <iostream>

int main() {
  static_assert(is_prime(100000000003ULL), "...");
  // static_assert(is_prime(1000003ULL), "...");
}
