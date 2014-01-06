#include <iostream>
#include <cstdlib>
#include <cerrno>
#include <string>
#include <limits>
#include <stdexcept>

namespace temp_fix
{
    int stoi( const std::string& str, std::size_t* pos = 0, int base = 10 )
    {
        const char* begin = str.c_str() ;
        char* end = nullptr ;
        long value = std::strtol( begin, &end, base ) ;

        if( errno == ERANGE || value > std::numeric_limits<int>::max() )
            throw std::out_of_range( "stoi: out ofrange" ) ;

        if( end == str.c_str() )
            throw std::invalid_argument( "stoi: invalid argument" ) ;

        if(pos) *pos = end - begin ;

        return value ;
    }
}

int main()
{
    const std::string test[] = { "1234", "-1234", "12345a6", "012", "0xabc",
                                 "a1234", "122345678912" } ;

    for( const std::string& str : test )
    {
        try
        {
            std::size_t pos = 0 ;
            std::cout << "str: " << str << " => " ;
            int value = temp_fix::stoi( str, &pos, 0 ) ;
            std::cout << "  value: " << value << "  pos: " << pos << '\n' ;
        }
        catch( const std::exception& e )
        {
            std::cerr << "*** error: " << e.what() << '\n' ;
        }
    }
}


