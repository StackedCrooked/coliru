#include <iostream>
#include <string>
#include <type_traits>

template < typename A, typename B >
typename std::common_type<A,B>::type maxv( A&& a, B&& b ) { return a<b ? b : a ; }

template < typename FIRST, typename... REST >
typename std::common_type<FIRST,REST...>::type maxv( FIRST&& first, REST&&... rest )
{ return maxv( first, maxv( std::forward<REST>(rest)... ) ) ; }

int main()
{
    const std::string str = "mnopqr" ;
    const char cstr[] = "uvwxyz" ;
    
    std::cout << maxv( 233, 23.8, 1200LL, 675243LL, 'A', 123456, short(32) ) << '\n'
              << maxv( str, cstr, "abcdef", std::string( 5, '!' ) ) << '\n' ;
              
    static_assert( std::is_same< std::string, decltype( maxv( str, cstr ) ) >::value , "unexpected" ) ;
}
