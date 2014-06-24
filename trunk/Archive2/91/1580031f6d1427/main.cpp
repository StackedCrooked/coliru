#include <bitset>
#include <iostream>
 
int main()
{
    std::bitset<4> b1("0110");
    std::bitset<4> b2("0011");
    std::cout << "b1 & b2: " << (b1 & b2) << '\n';
    std::cout << "b1 | b2: " << (b1 | b2) << '\n';
    std::cout << "b1 ^ b2: " << (b1 ^ b2) << '\n';
}