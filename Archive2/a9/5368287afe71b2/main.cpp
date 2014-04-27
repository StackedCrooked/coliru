#include <cstdint>
#include <iostream>

int
main()
{
    const uint32_t foo = 1 * 1024 /*KB*/ * 1024 /*MB*/ * 1024 /*GB*/ * 1024 /*TB*/ * 1024 /*PB*/; /* 1024 ^ 5 */
    const uint64_t bar = 1ul * 1024 /*KB*/ * 1024 /*MB*/ * 1024 /*GB*/ * 1024 /*TB*/ * 1024 /*PB*/; /* 1024 ^ 5 */
    std::cout << foo << std::endl;
    std::cout << std::hex << bar << std::endl;
}