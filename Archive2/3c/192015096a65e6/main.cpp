#include <iostream>
#include <sstream>


// calculates x + (x-1) + (x-2) ...
constexpr int sum(int x)
{
    // if x is only known at runtime then we can divide it
    // into compile-time "chunks" of 10
    // and sum(10) should be calculated at compile time
    // so this should be partially compile-time and partially runtime..?
    return x > 10 ? sum(10) + sum(x - 10)
            : x > 2 ? x + sum(x - 1)
            : x;
}


volatile int n = 123; // not optimizable


int main()
{
    std::cout << sum(n) << std::endl; // result is wrong..?
}
