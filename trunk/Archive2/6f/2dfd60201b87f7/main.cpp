#include <iostream>
#include <bitset>
 
int main()
{
    std::bitset<8> b;
    for (size_t i = 1; i < b.size(); i += 2) {
        b.set(i);
    }
    std::cout << 0x1c << '\n';
    std::cout << 0x4D3C2B1A << '\n';
    std::cout << 0x1A2B3C4D << '\n';
    std::cout << 0x7EE71E42 << '\n';
    std::cout << 0x2;
}