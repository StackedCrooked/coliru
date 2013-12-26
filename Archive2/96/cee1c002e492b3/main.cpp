#include <iostream>
using namespace std;
#define NUM 42

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

    cout << "Meta_fib(NUM)      : " << Fibonacci<NUM>::value << endl; // compile time :)
    cout << "Constexpr_fib(NUM) : " << fib(NUM) << endl;        // run time :-?
    std::array<int, Fibonacci<5>::value> arr;
    std::array<int, fib(5)> arr2;
    return 0;
}