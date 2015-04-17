#include <cstdint>

#define REDS2(x)    (((x) & 0xFFFF) + ((x) >> 16))

int main()
{
    constexpr auto r = REDS2(0xffffcfa0);
    static_assert( r == 0x0001cf9f, "bad result" );
    
    constexpr std::uint16_t s = REDS2(0xffffcfa0u);
    static_assert( s == 0x0000cf9fu, "bad result" );
}