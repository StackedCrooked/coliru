#include <iostream>
#include <bitset>
#include <vector>
#include <cstdint>
#include <algorithm>

constexpr std::size_t NBITS = 8 ;
using octet = std::bitset<NBITS> ;

std::vector<std::uint8_t> compress( const std::vector<unsigned int>& numbers )
{
    std::vector<std::uint8_t> compact ;

    if( !numbers.empty() )
    {
        const std::size_t maxv = *std::max_element( numbers.begin(), numbers.end() ) ;
        std::vector<octet> bits( maxv/NBITS + 1 ) ;
        for( unsigned int v : numbers ) bits[v/NBITS][ NBITS - v%NBITS - 1 ] = true ;

        for( const octet& i8 : bits ) compact.push_back( i8.to_ulong() ) ;
    }

    return compact ;
}

int main()
{
    std::vector<unsigned int> numbers ;
    for( unsigned int i = 0 ; i < 512 ; ++i ) if( i%3) numbers.push_back(i) ;

    auto compact = compress(numbers) ;
    
    int n = 0 ;
    for( std::uint8_t byte : compact )
    {
        std::cout << octet(byte) << ' ' ;
        if( ++n % 8 == 0 ) std::cout << '\n' ;  
    }
    std::cout << '\n' ;
}
