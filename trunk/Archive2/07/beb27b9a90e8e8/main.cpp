#include <iostream>
#include <type_traits>
#include <array>
#include <memory>
#include <algorithm>
#include <iomanip>

using byte = unsigned char ;

template < typename T > std::array< byte, sizeof(T) > to_bytes( T&& object )
{
    std::array< byte, sizeof(T) > bytes ;
    const byte* begin = reinterpret_cast< const byte* >( std::addressof( object ) ) ;
    std::uninitialized_copy( begin, begin + sizeof( T ), bytes.begin() ) ;
    return bytes ;
}

// *** invariant *** the input byte sequence was obtained by copying the underlying bytes
// ***************** of an initialised object of the trivially copyable type T                             
template < typename T, typename BYTE_SEQ > 
typename std::enable_if< std::is_trivially_copyable<T>::value >::type 
set_bytes( const BYTE_SEQ& bytes, T& object )  
{
    const auto obj_begin = reinterpret_cast< byte* >( std::addressof( object ) ) ;
    const auto n = std::min( bytes.size(), sizeof( T ) ) ;
    std::uninitialized_copy( std::begin( bytes ), std::begin( bytes ) + n, obj_begin ) ;
}

int main()
{
    unsigned long long i = 0x12'34'56'78'9a'bc ; // c++14 (same as: 0x123456789abc)
    const auto bytes = to_bytes(i) ;
    
    std::cout << "bytes (host-endian): " << std::hex ;
    for( auto byte : bytes ) std::cout << std::setw(2) << std::setfill('0') << unsigned(byte) << ' ' ;
    std::cout << '\n' ;
    
    i = 0 ;
    set_bytes( bytes, i ) ;
    std::cout << i << '\n' ;
}
