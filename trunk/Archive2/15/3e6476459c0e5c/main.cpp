// http://stackoverflow.com/questions/26852435/reasonably-portable-way-to-get-top-64-bits-from-64x64-bit-multiply
#include <iostream>
#include <cstdint>

//https://gcc.gnu.org/onlinedocs/gcc-4.8.1/gcc/_005f_005fint128.html#_005f_005fint128
using u128 = unsigned __int128;
using u64  = uint64_t;

void mul64x64( u64 a, u64 b, u64 & hi, u64 & lo ) {
    u128 product = u128(a) * b;
    lo = product;
    hi = product >> 64;
}

int main()
{
    u64 hi, lo;
    mul64x64( 40282220, u64{1} << 63, hi, lo );
    std::cout << hi << std::endl;
}