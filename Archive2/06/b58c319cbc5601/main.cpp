#include <iostream>

#include <cstdint>

int main()
{
    int32_t val = -(1L << 31);
    std::cout << "Before Division by -1 : " << val << std::endl;
    val = val / -1;
    std::cout << "After Division by -1  : " << val << std::endl;
}
