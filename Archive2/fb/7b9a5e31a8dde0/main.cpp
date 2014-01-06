#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iterator>
#include <vector>

template < typename STREAM_TYPE, STREAM_TYPE& stm >
struct basic_vstream
{
    template< typename T >
    static STREAM_TYPE& print_any( const T& v ) { return stm << v ; }

    template< typename FIRST, typename... REST >
    static STREAM_TYPE& print_any( const FIRST& first, const REST&... rest )
    {
        constexpr std::size_t n = sizeof...(rest) + 1 ;
        if( std::rand() % n == 0 ) return stm << first ;
        else return print_any(rest...) ;
    }

    template < typename... ARGS >
    const basic_vstream& operator() ( const ARGS&... args ) const
    {
        print_any(args...) ;
        return *this ;
    }

    // etc

    const basic_vstream& operator() ( STREAM_TYPE& (*manip)( STREAM_TYPE& ) ) const
    { stm << manip ; return *this ; }

    // other manipulators
};

using vstream = basic_vstream< std::ostream, std::cout > ;
using wvstream = basic_vstream< std::wostream, std::wcout > ;
constexpr vstream vout ;
constexpr wvstream wvout ;

int main()
{
    std::srand( std::time(nullptr) ) ;
    constexpr char space = ' ' ;

    for( int i=0 ; i < 12 ; ++i )
    {
        vout( "For", "In", "Within" ) (space)
            ( "a few", "two", 2, 2.5, "three", 3, 4.2 )(space)
            ( "seconds", "minutes", "hours", "days" )  (',') (space)
            ( "some", "two", 3, 4, "few" ) (space)
            ( "cats", "dogs", "boys", "girls" ) (space)
            ( "will", "should", "would", "might") ( "", " not" ) (space)
            ( "jump", "leap", "walk", "talk" ) (space)
            ( "over", "under", "beside", "atop", "to" )  (space)
            ( 'a', "one", "some", 1, "every", "each" ) (space)
            ( "tree", "car", "chair", "house" ) ('.') (std::endl) ;
    }
}
