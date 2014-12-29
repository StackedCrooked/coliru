#include <string>
#include <sstream>
#include <iostream>
#include <limits>
#include <stdexcept>

namespace my
{
    int stoi( std::string str )
    {
        std::istringstream stm(str) ;
        long long v = 0 ;

        if( stm >> v )
        {
            if( v < std::numeric_limits<int>::min() || v > std::numeric_limits<int>::max() )
                throw std::out_of_range( "my::stoi: out of range" ) ;
            return v ;
        }

        else throw std::invalid_argument( "my::stoi: invalid argument" ) ;
    }

    template < typename T > std::string to_string( const T& v )
    {
        std::ostringstream stm ;
        stm << v ;
        return stm.str() ;
    }
}

int main()
{
    const std::string test[] = { "1234", "-1234", "12345a6", "a1234", "122345678912" } ;

    for( const std::string& str : test )
    {
        try
        {
            std::cout << "str: " << str ;
            int v = my::stoi(str)  ;
            std::cout << " =>  " << v << " => " << my::to_string(v) << '\n' ;
        }
        catch( const std::exception& e )
        {
            std::cerr << "*** error: " << e.what() << '\n' ;
        }
    }
}
