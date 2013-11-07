#include <iostream>
#include <sstream>
#include <stdexcept>

struct hex_parse_error : std::invalid_argument
{
    explicit hex_parse_error( const std::string& str )
        : std::invalid_argument( "invalid hex string" ), bad_hex_string(str) {}

    const std::string bad_hex_string ;
};

unsigned int parse_hex( const std::string& str )
{
    std::istringstream stm(str) ;
    unsigned int v ;
    if( stm >> std::hex >> v && stm.eof() ) return v ;
    throw  hex_parse_error(str) ; // parse failed
}

int main()
{
    const std::string test[] = { "1000", "ffff", "abcd123", "abcy123" } ;

    try
    {
        for( const std::string& str : test )
        {
             std::cout << str << " : " ;
             std::cout << parse_hex(str) << '\n' ;
        }
    }

    catch( const hex_parse_error& e )
    {
        std::cerr << "parse error - invalid_argument: '" << e.bad_hex_string << "'\n" ;
    }
}
