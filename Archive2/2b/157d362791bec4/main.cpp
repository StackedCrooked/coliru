#include <iostream>

constexpr int ftbl[] { 1, 2, 3, 5, 8, 13 };
constexpr int fib(int n)
{
    return (n < sizeof(ftbl)/sizeof(*ftbl)) ? ftbl[n] : fib(n-2) + fib(n-1);
}

int main()
{
    std::cout << fib(1) << '\n';
    std::cout << fib(2) << '\n';
    std::cout << fib(6) << '\n';
}