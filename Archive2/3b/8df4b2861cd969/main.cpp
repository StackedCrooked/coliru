#include <alloca.h>
#include <cstddef>
#include <cstdint>

extern void g(void*);

void f(std::size_t n8, std::size_t n16, std::size_t n32) {
    std::int8_t* r8 = static_cast<std::int8_t*>(alloca(sizeof(std::int8_t) * n8));
    std::int16_t* r16 = static_cast<std::int16_t*>(alloca(sizeof(std::int16_t) * n16));
    std::int32_t* r32 = static_cast<std::int32_t*>(alloca(sizeof(std::int32_t) * n32));
    g(r8);
    g(r16);
    g(r32);
}