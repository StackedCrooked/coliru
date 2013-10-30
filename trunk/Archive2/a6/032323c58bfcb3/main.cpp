#include <iostream>
#include <string>
#include <algorithm>

std::string remove_letter_easy( std::string str, char c )
{
    str.erase( std::remove( str.begin(), str.end(), c ), str.end() ) ;
    return str ;
}

std::string remove_letter( std::string str, char c )
{
    for( auto iter = str.begin() ; iter != str.end() ; )
    {
        if( *iter == c ) iter = str.erase(iter) ;
        else ++iter ;
    }
    return str ;
}

int main()
{
    const std::string txt = "abcdefghabcdefghabcd" ;
    std::cout << txt << '\n' ;
    std::cout << remove_letter_easy( txt, 'b' ) << '\n' ;
    std::cout << remove_letter( txt, 'e' ) << '\n' ;
}
