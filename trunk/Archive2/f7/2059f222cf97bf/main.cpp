#include <iostream>
#include <limits>
#include <cstdint>
#include <cstring>

constexpr std::size_t BITS_PER_OCTET = 8 ;
static_assert( std::numeric_limits<unsigned char>::digits == BITS_PER_OCTET,
                                                          "byte is not an octect" ) ;
constexpr std::size_t BITS_PER_BLOCK = 512 ;
constexpr std::size_t BYTES_PER_BLOCK = BITS_PER_BLOCK / BITS_PER_OCTET ;

union block
{
    char bytes[BYTES_PER_BLOCK] ;
    std::uint32_t words[ BYTES_PER_BLOCK / sizeof(std::uint32_t) ] ;
};

template < std::size_t NBITS > union msg_chunk
{
    static_assert( NBITS % BITS_PER_BLOCK == 0, "bad size" ) ;

    char bytes[ NBITS / BITS_PER_OCTET ] {} ;
    block blocks[ sizeof(bytes) / sizeof(block) ] ;
};

int main()
{
    msg_chunk<4096> msg ;
    for( block& b : msg.blocks )
    {
        int v = 0 ;
        for( std::uint32_t& w : b.words ) w = v++ ;
    }

    char temp[ sizeof(msg) ] ;
    std::memcpy( temp, msg.bytes, sizeof(msg) ) ;
    std::memset( msg.bytes, 0, sizeof(msg) ) ;
    std::memcpy( msg.bytes, temp, sizeof(msg) ) ;

    for( block& b : msg.blocks )
    {
        for( std::uint32_t& w : b.words ) std::cout << w << ' ' ;
        std::cout << '\n' ;
    }
}
