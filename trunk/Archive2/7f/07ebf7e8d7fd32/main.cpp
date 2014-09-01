#include <cinttypes>
#include <cstdint>
#include <cstdio>
#include <type_traits>
 
 template< typename integer >
std::make_unsigned_t< decltype( + integer() ) >
promote_unsigned( integer value )
    { return value; }


int main()
{
    std::uint8_t a =  UINT8_MAX; a *= promote_unsigned( a );
    std::uint16_t b = UINT16_MAX; b *= promote_unsigned( b );
    std::uint32_t c = UINT32_MAX; c *= promote_unsigned( c );
    std::uint64_t d = UINT64_MAX; d *= promote_unsigned( d );
 
    std::printf("%02" PRIX8 " %04" PRIX16 " %08" PRIX32 " %016" PRIX64 "\n",
        a, b, c, d);
 
    return 0;
}