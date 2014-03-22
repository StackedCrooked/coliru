#include <iostream>
#include <string>

const std::string ws = " \t\n" ;

// trim leading whitespace
std::string trim_leading_ws( const std::string& str )
{
     // http://www.cplusplus.com/reference/string/string/find_first_not_of/
     const auto pos = str.find_first_not_of(ws) ;
     return pos != std::string::npos ? str.substr(pos) : "" ;
}

// trim trailing whitespace
std::string trim_trailing_ws( const std::string& str )
{
     //http://www.cplusplus.com/reference/string/string/find_last_not_of/
     const auto pos = str.find_last_not_of(ws) ;
     return pos != std::string::npos ? str.substr( 0, pos+1 ) : "" ;
}

// trim trailing and trailing whitespace
std::string trim( const std::string& str )
{ return trim_trailing_ws( trim_leading_ws(str) ) ; }

const std::string leading_delimiters = "(<[{" ;
const std::string trailing_delimiters = ")>]}" ;

// determine corresponding ending delimiter character
char ending_delimiter( char starting_delimiter )
{
    const auto pos = leading_delimiters.find(starting_delimiter) ;
    if( pos != std::string::npos ) return trailing_delimiters[pos] ;
    else return 0 ;
}

int main()
{
    std::string str = "    (<({[  hello world!  ]>)>)    " ;
    str = trim(str) ;
    std::cout << '\n' << str << "\n012345678901234567890123456789\n\n" ;

    const auto size = str.size() ;

    for( std::size_t i = 0 ; i < size ; ++i )
    {
        char end_delim = ending_delimiter( str[i] ) ;
        if( end_delim )
        {
            if( str[ size - i - 1 ] != end_delim )
            {
                std::cout << "mismatched deliniter at position " << i << '\n'
                          << "tried to match '" << str[i] << "' expected '" << end_delim
                          << "' got '" << str[ size - i - 1 ] << "'\n" ;
                break ;
            }
        }
        else break ;
    }
}
