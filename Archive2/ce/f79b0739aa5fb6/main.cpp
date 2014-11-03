#include <iostream>

constexpr std::uintmax_t fibo(std::uintmax_t n,
                              std::uintmax_t a = 0, std::uintmax_t b = 1)
{
    return n < 2? n : a + fibo(n-1, b, a+b);
}

int main ()
{
	for (auto i = 0; i != 20; ++i)
	std::cout << fibo(i) << " ";
}
