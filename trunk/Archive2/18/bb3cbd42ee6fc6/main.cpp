#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>
#include <cstdint>
#include <algorithm>

int main()
{
    const std::size_t NBITS_ELEMENT = 32 ; // 32 bits in std::uint32_t
    const std::size_t NBITS_MODULUS = 256 ;

    static_assert( NBITS_MODULUS%NBITS_ELEMENT == 0, "integral multiple" ) ;
    // the elements to be considered are the ones that will
    // contribute to the least significant NBITS_MODULUS bits
    const std::size_t N = NBITS_MODULUS / NBITS_ELEMENT ;

    const std::size_t SZ = 16 ;
    std::uint32_t arr[SZ] ; // most significant 32 bits at arr[0]
    // fill array with values 10, 11, 12, ...
    std::iota( arr, arr+SZ, 10 ) ;

    for( std::uint32_t v : arr ) std::cout << v << ' ' ;
        std::cout << '\n' ;

    {
        std::uint32_t arr_mod_result[N] ;
        std::copy( arr+SZ-N, arr+SZ, arr_mod_result ) ;

        std::cout << "mod result (as array): " ;
        for( std::uint32_t v : arr_mod_result ) std::cout << v << ' ' ;
        std::cout << '\n' ;
    }


    {
        std::cout << "\n------------------\nmod result (as big number):\n" ;
        using boost::multiprecision::cpp_int ;

        cpp_int result ;
        for( std::size_t i = SZ-N ;  i < SZ ; ++i ) // pick up the last N values
        {
            const std::size_t shl = (SZ-i-1) * NBITS_ELEMENT ;
            std::cout << arr[i] << " << " << shl << " +\n" ;
            result += ( cpp_int(arr[i] ) << shl ) ; // shift and add
        }

        std::cout << "-----------\n== " << result << '\n' ;
    }
}
