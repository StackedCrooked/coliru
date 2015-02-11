#include <iostream>
#include <limits>
#include <cstdio>

template<typename T> __attribute__((noinline))
bool test(T x)
{
    return x < x + 1;   
}

int main()
{
    std::printf("%i %i\n", test<char>(0), test(std::numeric_limits<char>::max()));
    std::printf("%i %i\n", test<int>(0), test(std::numeric_limits<int>::max()));
}
