#include <iostream>

constexpr int f()
{
    return 1;
}

int main()
{
    constexpr int x = 1;
    constexpr int y = 2;
    const int i = (x > y) ? x : y;
    std::cout << i;
}