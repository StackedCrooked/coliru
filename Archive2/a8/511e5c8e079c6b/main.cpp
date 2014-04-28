#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <sstream>

struct one_of
{
    void one_of_( const one_of& v  ) { selected = v.selected ; }

    template< typename T > void one_of_( const T& v  )
    { std::ostringstream stm ; stm << v ; selected = stm.str() ; }

    template< typename FIRST, typename... REST >
    void one_of_( const FIRST& first, const REST&... rest )
    {
        const std::size_t n = sizeof...(rest) + 1 ;
        if( std::rand() % n == 0 ) one_of_(first) ;
    	else one_of_(rest...) ;
    }

    template < typename... ARGS > explicit one_of( const ARGS&... args )
    { one_of_(args...) ; }

    std::string selected ;
};

template < typename OSTREAM_TYPE >
OSTREAM_TYPE& operator<< ( OSTREAM_TYPE& stm, const one_of& v ) { return stm << v.selected ; }

int main()
{
    std::srand( std::time(nullptr) ) ;

    for( int i=0 ; i < 10 ; ++i )
        std::cout << one_of( 1, 2, 3, one_of( 4, "five", one_of( 6, "seven", 8 ) ), 9 ) << ' '
            << one_of( "one", one_of(1,2,3) ) << ' ' << one_of( "six", one_of(7,8,9) ) << '\n' ;
}
