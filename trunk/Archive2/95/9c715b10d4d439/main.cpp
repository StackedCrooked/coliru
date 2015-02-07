#include <array>
#include <memory>
#include <type_traits>
#include <iostream>
#include <iomanip>

using byte = unsigned char ;

template< typename T > std::array< byte, sizeof(T) >  to_bytes( const T& object )
{
    std::array< byte, sizeof(T) > bytes ;

    const byte* begin = reinterpret_cast< const byte* >( std::addressof(object) ) ;
    const byte* end = begin + sizeof(T) ;
    std::copy( begin, end, std::begin(bytes) ) ;

    return bytes ;
}

template< typename T >
T& from_bytes( const std::array< byte, sizeof(T) >& bytes, T& object )
{
    // http://en.cppreference.com/w/cpp/types/is_trivially_copyable
    static_assert( std::is_trivially_copyable<T>::value, "not a TriviallyCopyable type" ) ;

    byte* begin_object = reinterpret_cast< byte* >( std::addressof(object) ) ;
    std::copy( std::begin(bytes), std::end(bytes), begin_object ) ;

    return object ;
}

int main()
{
    double d = 123.456789 ;
    const auto bytes = to_bytes(d) ;

    std::cout << std::hex << std::setfill('0') ;
    for( byte b : bytes ) std::cout << std::setw(2) << int(b) << ' ' ;
    std::cout << '\n' ;

    d = 0 ;
    from_bytes( bytes, d ) ;
    std::cout << std::fixed << d << '\n' ;

    int arr[] = { 1, 63, 256, 511, 1024 } ;
    const auto array_bytes = to_bytes(arr) ;

    for( byte b : array_bytes ) std::cout << std::setw(2) << int(b) << ' ' ;
    std::cout << '\n' ;
    
    for( int& v : arr ) v = -1 ;
    from_bytes( array_bytes, arr ) ;
    for( int v : arr ) std::cout << std::dec << v << ' ' ;
    std::cout << '\n' ;
}
