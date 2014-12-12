#include <iostream>
#include <limits>
#include <cstdint>

int main()
{
    std::cout << std::numeric_limits<int>::max() << std::endl;
    std::cout << std::numeric_limits<uint32_t>::max() << std::endl;
    return 0;
}