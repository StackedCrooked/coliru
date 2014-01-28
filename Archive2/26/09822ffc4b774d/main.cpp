#include <iostream>
#include <type_traits>

template < typename T, std::size_t N >
constexpr std::size_t size( T(&)[N] ) { return N ; }

int main()
{
    const int a[] = { 0, 1, 2, 3, 4 } ;

    int b[ size(a) ] {} ;

    int c[ std::extent< decltype(a) >::value  ] {} ;

    int d[ size(a) ][ size(b)*2 ][ size(c)*3 ] {} ;

    std::cout << size(d) << ' ' << std::extent< decltype(d) >::value << '\n' ;
    std::cout << size( d[0] ) << ' ' << std::extent< decltype(d), 1 >::value << '\n' ;
    std::cout << size( d[0][0] ) << ' ' << std::extent< decltype(d), 2 >::value << '\n' ;
}
