#include <iostream>
#include <cstdio>

namespace detail_
{
    char* to_string( int v, char* cstr, std::size_t n )
    { return std::snprintf( cstr, n, "%d", v ) > 0 ? cstr : nullptr ; }

    template < std::size_t N > char* to_string( int v, char (&array)[N] )
    { return to_string( v, array, N ) ; }

    char* to_string( double v, char* cstr, std::size_t n )
    { return std::snprintf( cstr, n, "%f", v ) > 0 ? cstr : nullptr ; }

    template < std::size_t N > char* to_string( double v, char (&array)[N] )
    { return to_string( v, array, N ) ; }

    // etc ...
    // one overload per supported type
}

struct my_struct
{
    template < typename T >
    static char* to_string( T&& v, char* cstr, std::size_t n )
    { return detail_::to_string( v, cstr, n ) ; }

    template < typename T, std::size_t N >
    static char* to_string( T&& v, char (&array)[N] )
    { return detail_::to_string( v, array ) ; }
};

int main()
{
    char cstr[100] ;
    std::cout << my_struct::to_string( 1234, cstr ) << '\n' ;
    std::cout << my_struct::to_string( 12.34, cstr ) << '\n' ;
}
