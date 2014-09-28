#include <iostream>
#include <bitset>
#include <cstdint>
#include <limits>

int main()
{
    const int N = 10 ;
    int  x[N];

    for( int i = 0; i < N ; ++i )
    {
        x[i] = 1;
        const int* address = x + i ;
        const std::uintptr_t address_value = reinterpret_cast<std::uintptr_t>(address) ;

        const int NBITS = std::numeric_limits<std::uintptr_t>::digits ;
        const std::bitset<NBITS> bits(address_value) ;
        const std::string bitstr = bits.to_string() ;

        std::cout << "decimal: " << std::dec << address_value
                  << std::showbase << std::oct << "   octal: " << address_value
                  << std::hex << "   hex: " << address_value
                  << "    bits: " ;
       const int NIBBLE = 4 ;
       for( int i = 0 ; i < NBITS/NIBBLE ; ++i ) std::cout << bitstr.substr( i*NIBBLE, NIBBLE ) << ' ' ;
       std::cout << '\n' ;
    }
}
