#include <array>
#include <limits>
#include <iostream>
#include <stdint.h>


int main()
{
    std::array<int, std::numeric_limits<size_t>::max()> data;
    std::cout << data[time(0)] << std::endl;
}