#include <cassert>
#include <cstddef>

using std::size_t;

// Precondition: (low % 2 == 0) && (high % 2 == 0)
constexpr bool has_odd_factor_between(size_t number, size_t low, size_t high)
{
  return (low + 1 >= high ? (number % low == 0 ? true : false)
            : (has_odd_factor_between(number, low, low + (high - low) / 2) ||
               has_odd_factor_between(number, low + (high - low) / 2, high)));
}

constexpr bool is_prime_func(size_t number)
{
  return number > 1 && (number == 2 || (number % 2 == 1 && (number == 3 || !has_odd_factor_between(number, 3, number / 2 + 1))));
}

int main(void)
{
   static_assert(is_prime_func(100000000003ULL), "...");  // Computed at compile-time
}
