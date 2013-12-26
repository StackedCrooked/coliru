#include <iostream>
using namespace std;
#define NUM 10

template <unsigned int N>
struct Fibonacci {
    enum { value = Fibonacci<N - 1>::value + Fibonacci<N - 2>::value };
};

template <>
struct Fibonacci<1> {
    enum { value = 1 };
};

template <>
struct Fibonacci<0> {
    enum { value = 1 };
};

constexpr unsigned int fib(unsigned int n)
{
    return (n > 1 ? fib(n-1) + fib(n-2) : 1 );
}

#include <array>

int main()
{
    constexpr int num = 5;
    std::array<int, Fibonacci<num>::value> arr;
    std::array<int, fib(num)> arr2;
    return 0;
}