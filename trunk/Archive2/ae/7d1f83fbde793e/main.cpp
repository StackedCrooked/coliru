#include <iostream>
#include <string>
#include <cstring>

std::string re_format( std::string name_space_dddeeee )
{
    const auto sz = name_space_dddeeee.size() ;

    if( sz <= 9 ) return "string is too small" ;

    auto name_end = sz - 9 ;

    return name_space_dddeeee.substr(0,name_end) + // "name"
           name_space_dddeeee.substr( name_end, 5 ) + '-' + // ", ddd-"
           name_space_dddeeee.substr( name_end+5 ) ; // "eeee"

}

char* re_format( char cstr[], std::size_t n )
{
    const std::string str = re_format(cstr) ;
    return str.size() < n ? std::strcpy( cstr, str.c_str() ) : nullptr ;
}

int main()
{
    char cstr[128] = "Andrew R. Koenig, 1234567" ;
    if( re_format( cstr, sizeof(cstr) ) ) std::cout << cstr <<'\n' ;
}
