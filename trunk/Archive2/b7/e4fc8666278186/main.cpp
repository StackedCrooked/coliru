#include <cstdint>

uint32_t f(uint32_t x) {
    return (x << 2) | (x >> 30);
}