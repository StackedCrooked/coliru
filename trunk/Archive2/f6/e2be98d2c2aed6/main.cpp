#include <cstdint>

constexpr uint64_t ct_mid(uint64_t lo, uint64_t hi)
{
    return (lo + hi + 1) / 2;
}

constexpr uint64_t sqrt_helper(uint64_t x, uint64_t lo, uint64_t hi, uint64_t mid)
{
  return lo == hi ? lo : ((x / mid < mid)
      ? sqrt_helper(x, lo, mid-1, ct_mid(lo, mid-1))
      : sqrt_helper(x, mid, hi, ct_mid(mid, hi)));
}

constexpr uint64_t sqrt_helper_(uint64_t x, uint64_t lo, uint64_t hi)
{
    return sqrt_helper(x, lo, hi, ct_mid(lo, hi));
}

constexpr uint64_t ct_sqrt(uint64_t x)
{
  return sqrt_helper_(x, 0, (x < 9) ? x : x - 1);
}

int main()
{
    constexpr auto x = ct_sqrt(uint64_t(1)<<30);
}