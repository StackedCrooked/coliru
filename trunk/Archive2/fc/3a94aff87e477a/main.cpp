#include <cmath>
#include <cstdint>
#include <limits>
#include <iostream>
#include <cstdio>

int main() {
    using namespace std;
    
    uint32_t result = std::lround(0.82004366063971901 * std::numeric_limits<uint32_t>::max());
    printf("%lf -> %u (0x%X)\n", 0.82004366063971901, result, result);
    
    result = std::lround(0.5 * std::numeric_limits<uint32_t>::max());
    printf("%lf -> %u (0x%X)\n", 0.5, result, result);
    
    result = std::lround(0.0 * std::numeric_limits<uint32_t>::max());
    printf("%lf -> %u (0x%X)\n", 0.0, result, result);
    
    result = std::lround(1.0 * std::numeric_limits<uint32_t>::max());
    printf("%lf -> %u (0x%X)\n", 1.0, result, result);
}