#include <iostream>
#include <cctype>
#include <string>

void to_lower( char* s )
{
    if( s != nullptr )
        for( ; *s ; ++s ) *s = std::tolower( *s ) ;
}

std::string to_lower( std::string s )
{
    for( char& c : s ) c = std::tolower(c) ;
    return s ;
}

int main()
{
    char cstr[] = "HELLO WORLD!\n" ;
    to_lower(cstr) ;
    std::cout << cstr ;

    const std::string str = "HELLO AGAIN!\n" ;
    std::cout << to_lower(str) ;
}
