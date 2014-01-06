#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iterator>
#include <sstream>

template < typename STREAM_TYPE, STREAM_TYPE& stm >
struct basic_vstream
{
    template< typename T >
    static void print_any( const T& v ) { stm << v ; }

    template< typename FIRST, typename... REST >
    static void print_any( const FIRST& first, const REST&... rest )
    {
        constexpr std::size_t n = sizeof...(rest) + 1 ;
        if( std::rand() % n == 0 ) stm << first ;
        else print_any(rest...) ;
    }

    template < typename... ARGS >
    const basic_vstream& operator() ( const ARGS&... args ) const
    {
        print_any(args...) ;
        return *this ;
    }
};

std::stringstream stm ;
const basic_vstream< std::stringstream, stm > svout ;

int main()
{
    std::srand( std::time(nullptr) ) ;
    constexpr char space = ' ' ;

    for( int i=0 ; i < 12 ; ++i )
    {
       svout( "For", "In", "Within" ) (space)
            ( "a few", "two", 2, 2.5, "three", 3, 4.2 )(space)
            ( "seconds", "minutes", "hours", "days" )  (',') (space)
            ( "some", "two", 3, 4, "few" ) (space)
            ( "cats", "dogs", "boys", "girls" ) (space)
            ( "will", "should", "would", "might") ( "", " not" ) (space)
            ( "jump", "leap", "walk", "talk" ) (space)
            ( "over", "under", "beside", "atop", "to" )  (space)
            ( 'a', "one", "some", 1, "every", "each" ) (space)
            ( "tree", "car", "chair", "house" ) ( ". " ) ;

        if( i%5 == 4 ) svout( "\n\n" ) ;
    }

    const int line_sz = 40 ;

    std::string line ;
    while( std::getline( stm, line ) )
    {
        if( line.empty() ) std::cout << '\n' ;
        else
        {
            for( std::size_t sz = 0 ; sz < line.size() ; sz += line_sz )
            {
                std::string s = line.substr( sz, line_sz ) ;
                if( s.size() == line_sz ) while( !std::isspace( s.back() ) )
                {
                    s.pop_back() ;
                    --sz ;
                }
                std::cout << s << '\n' ;
            }
        }
    }
}
