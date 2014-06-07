#include <iostream>
#include <bitset>
#include <climits>

unsigned int f(bool comp)
{
    unsigned int z = -comp;
    return z;
}

int main()
{
    std::cout << std::bitset<sizeof(bool)*CHAR_BIT>(f(true)) << ' '
              << std::bitset<sizeof(bool)*CHAR_BIT>(f(false)) << '\n';
}