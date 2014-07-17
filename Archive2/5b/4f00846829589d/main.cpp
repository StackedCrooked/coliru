// Compile on a recent version of clang and run it:
// clang++ -std=c++11 -O3 -Wall -fsanitize=undefined main.cpp -o stdint16

#include <cinttypes>
#include <cstdint>
#include <cstdio>

int main()
{
    unsigned short u16 = UINT16_MAX; u16 *= u16; // Standard says this is defined, and modulo 2^16

    std::printf(" %04" PRIX16 "\n", u16 );

    return 0;
}