#include <iostream>
#include <limits>
#include <cstdio>

__attribute__((noinline))
bool test(int x)
{
    return x < x + 1;   
}

int main()
{
    std::printf("%i %i", test(0), test(std::numeric_limits<int>::max()));
}
