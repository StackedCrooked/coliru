#include <iomanip>
#include <iostream>
#include <stdint.h>


uint8_t data[] = { 0x53, 0x1, 0x2 };


int main()
{
    std::cout << std::hex;
    std::cout << "0x" << std::setw(2) << std::setfill('0') << static_cast<int>(data[0]) << std::endl;
    std::cout << "0x" << std::setw(2) << std::setfill('0') << static_cast<int>(data[1]) << std::endl;
    std::cout << "0x" << std::setw(2) << std::setfill('0') << static_cast<int>(data[2]) << std::endl;
}