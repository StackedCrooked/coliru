#include <array>
#include <iostream>
#include <stdint.h>


int main()
{
    std::array<int, uint64_t(-1)> data;
    std::cout << "Data size: " << data.size() << std::endl;
    
    data[42] = 3;
    std::cout << data[42] << std::endl;
}