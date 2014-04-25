#include <cstring>
#include <memory>

void foo( char* begin, std::size_t n )
{
    for( std::size_t i = 0 ; i < n ; ++i ) begin[i] = ' ' ; 
    // 'calls' std::memset
}

void bar( char* begin, std::size_t n )
{
    for( auto end = begin+n ; begin != end ; ++begin ) *begin = ' '  ;
    // 'calls' std::memset
}

void baz( char* begin, std::size_t n )
{
    std::uninitialized_fill( begin, begin+n, ' ' ) ;
    // 'calls' std::memset
}

void foobar( char* begin, std::size_t n )
{
    std::memset( begin, ' ', n ) ;
    // 'calls' std::memset
}
