#include <iostream>
#include <stdint.h>
#include <limits>

uint64_t fix_factor = static_cast< uint64_t >( std::numeric_limits< uint32_t >::max() ) + 1;

uint32_t a = (7./13) * fix_factor;
uint32_t b = (13./14) * fix_factor;
uint32_t prod = static_cast< uint64_t >( a ) * b / fix_factor;

int main() {
    std::cerr << double( prod ) / fix_factor << '\n';
}
