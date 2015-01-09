#include <iostream>

int main()
{
    int a = 20;
    int b = 66;

    // before swapping
    std::cout << a  << ' ' << b  << '\n';

    // swap
    a ^= b ^= a ^= b;

    // after swapping
    std::cout << a << ' ' << b << '\n';
}