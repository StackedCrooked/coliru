#include <iostream>
#include <sstream>
int main()
{
    uint8_t c = 42;
    std::cout << "The number 42 in hex:   " << std::hex << c << '\n';
    std::cout << "The number 42 in hex (signed cast):   " << std::hex << static_cast<signed>(c) << '\n';
    std::cout << "The number 42 in hex (unsigned cast):   " << std::hex << static_cast<unsigned>(c) << '\n';
}