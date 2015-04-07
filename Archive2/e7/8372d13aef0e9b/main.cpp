#include <iostream>
#include <string>
#include <vector>
#include <bitset>

int main()
{
    std::bitset<4> b(3);
    std::cout << b.to_string() << std::endl;
    std::cout << "bit 0: " << b.test(0) << std::endl;
    std::cout << "bit 1: " << b.test(1) << std::endl;
    std::cout << "bitset val: " << b.to_ulong() << std::endl;
    
    return 0;
}
