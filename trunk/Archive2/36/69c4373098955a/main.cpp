
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <tuple>

constexpr int pow(int val, int pow) noexcept
{
    int res = val;
    for (int i = 0; i < pow; i++) res *= val;
    return res;
}

template<int stage>
struct Fib
{
  static const uint64_t value = Fib<stage-1>::value + Fib<stage-2>::value;

};

template<>
struct Fib<0>
{
  static const uint64_t value = 0;

};

template<> 
struct Fib<1>
{
  static const uint64_t value = 1;
};


int main()
{
    std::cerr << Fib<pow(3,3)>::value << std::endl;
}