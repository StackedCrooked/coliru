#include <bitset>
#include <iostream>

int main()
{
    std::bitset<1234> bits;
    bits.flip();
    std::cout << bits << '\n';
}
