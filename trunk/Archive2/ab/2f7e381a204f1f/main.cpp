#include <iostream>
#include <ctime>
#include <functional>
#include <algorithm>
#include <numeric>

int foo( int a ) ;
std::function< int(int) > wrapped_closure() ;

template < std::size_t N > int bar( const int (&srce)[N], int (&dest)[N], const std::function< int(int) >& fn )
{
    const auto start = std::clock() ;
    std::transform( srce, srce+N, dest, fn ) ;
    return ( std::clock() - start ) * 1000.0 / CLOCKS_PER_SEC ;
}

int main()
{
    constexpr std::size_t N = 1024*1024*64 ;
    static int srce[N] {};
    static int dest[N] {};
    std::iota( srce, srce+N, 0 ) ;
    std::iota( dest, dest+N, 0 ) ; // **** added

    std::cout << "function pointer: " <<  bar( srce, dest, &foo ) << " millisecs\n" ;
    std::cout << "  lambda (local): " <<  bar( srce, dest, []( int a ) { return a/2 + a%3 ; } ) << " millisecs\n" ;
    std::cout << " lambda (extern): " <<  bar( srce, dest, wrapped_closure() ) << " millisecs\n" ;
    std::cout << " lambda (extern): " <<  bar( srce, dest, wrapped_closure() ) << " millisecs\n" ;
    std::cout << "  lambda (local): " <<  bar( srce, dest, []( int a ) { return a/2 + a%3 ; } ) << " millisecs\n" ;
    std::cout << "function pointer: " <<  bar( srce, dest, &foo ) << " millisecs\n" ;
}
