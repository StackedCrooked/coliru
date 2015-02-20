#include <iostream>
#include <cstdint>

int main()
{
    uintptr_t a = 0x400040 - 0x400000 + 0x10;
    uintptr_t b = 0x400040 - (0x400000 + 0x10);
    std::cout << a << std::endl;
    std::cout << b << std::endl;
}

