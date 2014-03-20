#include <iostream>
#include <bitset>

constexpr unsigned CLog2(unsigned n, unsigned p = 0) {
    return (n <= 1) ? p : CLog2(n / 2, p + 1);
}

int main()
{
    constexpr size_t bitCount = CLog2(4);
    std::bitset<bitCount> bits;
    std::cout << bits << '\n';
}
