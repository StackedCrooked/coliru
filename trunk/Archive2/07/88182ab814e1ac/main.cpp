#include <iostream>
#include <string>

bool is_double( const std::string& str )
{
    std::size_t pos = 0 ;

    try { std::stod( str, &pos ) ; }
    catch(...) { return false ; }

    for( auto i = pos ; i < str.size() ; ++i )
        if( !std::isspace( str[pos] ) ) return false ;

    return true ;
}

int main()
{
    for( std::string str : { "12", "12.", "-12.e+23", "+0xabc.dP-5", "-Infinity", "NaN", "inf", "nan", // all true
                             "-12.e+0x23", "vjvj", "12.34.56", "12.e" } ) // all false
    {
        std::cout << str << " => " << std::boolalpha << is_double(str) << '\n' ;
    }
}
