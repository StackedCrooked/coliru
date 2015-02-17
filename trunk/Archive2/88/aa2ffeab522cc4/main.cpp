#include <cstddef>
#include <cstdint>

extern void g(void*);

void f(std::size_t n8, std::size_t n16, std::size_t n32) {
    std::int8_t r8[n8];
    std::int8_t r16[n16];
    std::int8_t r32[n32];
    g(r8);
    g(r16);
    g(r32);
}