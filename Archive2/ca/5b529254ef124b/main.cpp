#include <iostream>
#include <string>

const std::string ws = " \t\n" ;
const std::string leading_delimiters = "(<[{" ;
const std::string trailing_delimiters = ")>]}" ;

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

// find starting delimiters
std::string find_starting_delimiters( std::string str )
{
     str = trim_leading_ws(str) ;
     const auto pos = str.find_first_not_of(leading_delimiters) ;
     return pos != std::string::npos ? str.substr(0,pos) : "" ;
}

// determine ending delimiters given the starting delimiters
std::string determine_ending_delimiters( const std::string& starting_delimiters )
{
    std::string temp ;

    // http://www.stroustrup.com/C++11FAQ.html#for
    for( char c : starting_delimiters )
    {
        // http://www.cplusplus.com/reference/string/string/find/
        const auto pos = leading_delimiters.find(c) ;
        if( pos != std::string::npos ) temp += trailing_delimiters[pos] ;
        else break ;
    }

    // ending delimiters must be in reverse order of starting delimiters
    return std::string( temp.rbegin(), temp.rend() ) ;
}

int main()
{
    std::string str = "    (<({[hello world!]})>)    " ;
    std::cout << "original: " << str << '\n' ;

    str = trim(str) ;
    std::cout << "trimmed: " << str << '\n' ;

    const std::string start_delims = find_starting_delimiters(str) ;
    std::cout << "starting delimiters: " << start_delims << '\n' ; // (<({[

    const std::string ending_delims = determine_ending_delimiters(start_delims) ;
    std::cout << "corresponding ending delimiters: " << ending_delims << '\n' ; // ]})>)
    
    // TODO: does the string str end with ending_delims?
    // TODO: if not, where is the mismatch?
}
