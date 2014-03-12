#include <iostream>
#include <cstring>
#include <string>
#include <cstdint>
#include <sstream>
#include <vector>

int main()
{
    const char* const typical_response = "0E1D" "052B" "FBB7" "11C1" "002C" "0042"
                "007A" "014D" "FE44" "022B" "270F" "7FFF" "8000" "0000" "0000" "0000" ;

    constexpr std::size_t RESP_SZ = 64 ;
    char response[RESP_SZ] ;
    std::memcpy( response, typical_response, RESP_SZ ) ;

    std::vector<int> numbers ;

    // every 4 characters above are a signed decimal value
    constexpr std::size_t NCHARS = 4 ;
    for( std::size_t i = 0 ; i < RESP_SZ ; i += NCHARS ) // in 4 char chunks
    {
        std::istringstream stm( std::string( response+i, response+i+NCHARS ) ) ;

        using uint_type = std::uint16_t ;
        using sint_type = std::int16_t ;
        uint_type value ;
        if( stm >> std::hex >> value ) numbers.push_back( sint_type(value) ) ;
    }

    for( int n : numbers ) std::cout << n << ' ' ;
    std::cout << '\n' ;
}
