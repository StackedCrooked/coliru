#include <iomanip>
#include <iostream>
#include <stdint.h>

int main()
{
    uint16_t n = 0xabcd;
    
    // Binary representation
    uint8_t * b = static_cast<uint8_t*>(static_cast<void*>(&n));
    std::cout << std::hex << "0x"
              << std::setw(2) << std::setfill('0') << int(b[0])
              << std::setw(2) << std::setfill('0') << int(b[1])
              << std::dec << std::endl;
                
                
    // Using bit operations.
    std::cout << "0x" << std::hex << std::setw(4) << std::setfill('0') << int(n & 0xff00) << std::endl;
    std::cout << "0x" << std::hex << std::setw(4) << std::setfill('0') << int(n & 0x00ff) << std::endl;
}