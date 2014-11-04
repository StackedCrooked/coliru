#include <cstdint>

constexpr std::uintmax_t fibo(std::uintmax_t n,
                              std::uintmax_t a = 0, std::uintmax_t b = 1)
{
    return n < 2? n : a + fibo(n-1, b, a+b);
}

std::uintmax_t f(std::uintmax_t n) { return fibo(n); }
