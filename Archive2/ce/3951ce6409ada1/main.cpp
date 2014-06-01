#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

struct centre
{
    template < typename T > centre( unsigned int width, const T& v ) : width(width) { put(v) ; }

    template < typename... T > centre( unsigned int width, const T&... v ) : width(width) { put(v...) ; }

    template < typename T > void put( const T& v ) { stm << v ; }

    template < typename FIRST, typename... REST >
    void put( const FIRST& first, const REST&... rest ) { stm << first ; put(rest...) ; }

    std::string value() const
    {
        std::string result = stm.str() ;

        if( width > result.size() )
        {
            auto n = width - result.size() ;
            if( n > 1 ) result = std::string( n/2, ' ' ) + result ;
            result += std::string( (n+1) / 2, ' ' ) ;
        }

        return result ;
    }

    const unsigned int width ;
    std::ostringstream stm ;
};

std::ostream& operator<< ( std::ostream& stm, const centre& c ) { return stm << c.value() ; }

int main()
{
    std::cout << '|' << centre( 40, "hello world" ) << "|\n"
              << '|' << centre( 40, "first value: ", std::fixed, std::setprecision(2), 6.7 ) << "|\n"
              << '|' << centre( 40, "the second value is: ", std::setw(6), std::internal, std::setfill('0'), -123 ) << "|\n" ;
}
