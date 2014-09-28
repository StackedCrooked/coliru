#include <iostream>
#include <bitset>
#include <cstdint>
#include <limits>

int main()
{
    const int N = 8 ;
    int  x[N];

    for( int i = 0; i < N ; ++i )
    {
        x[i] = 1;
        const int* address = x + i ;
        const std::uintptr_t address_value = reinterpret_cast<std::uintptr_t>(address) ;

        const int NBITS = std::numeric_limits<std::uintptr_t>::digits ;
        const std::bitset<NBITS> bits(address_value) ;
        const std::string bitstr = bits.to_string() ;

        std::cout << std::dec << i << ". decimal: " << address_value
                  << std::showbase << std::oct << "   octal: " << address_value
                  << std::hex << "   hex: " << address_value
                  << "    bits: " ;
       const int NIBBLE_SZ = 4 ;
       for( int j = 0 ; j < NBITS/NIBBLE_SZ ; ++j ) std::cout << bitstr.substr( j*NIBBLE_SZ, NIBBLE_SZ ) << ' ' ;
       std::cout << '\n' ;
    }
}
