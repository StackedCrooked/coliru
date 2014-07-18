// Compile on a recent version of clang and run it:
// clang++ -std=c++11 -O3 -Wall -fsanitize=undefined main.cpp -o stdint16 && ./stdint16
// g++ -std=c++11 -O3 -Wall -ftrapv main.cpp -o stdint16 && ./stdint16
//
#include <cinttypes>
#include <cstdint>
#include <cstdio>

int main()
{
    /*
     * http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2012/n3337.pdf
     *
     * 3.9.1 Fundamental types [basic.fundamental]
     *
     */
    uint16_t u = UINT16_MAX; u = u * u; // Standard says this is defined, and modulo 2^16

    std::printf(" %04" PRIX16 "\n", u );

    int64_t c = u * u;
    
    std::printf(" %ld\n", c );
        
    uint16_t a = 65535, b = 65534; int diff = b - a;
    
    std::printf(" %d\n", diff );
    
    return 0;
}