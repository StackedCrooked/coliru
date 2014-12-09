#include <iostream>
#include <string>

std::string reverse( std::string str )
{
    if( str.size() < 2 ) return str ;
    return reverse( str.substr(1) ) + str[0]  ;
}

int main()
{
    for( std::string s : { "", "a", "ab", "abcdefgh" } ) 
        std::cout << s << " : " << reverse(s) << '\n' ;
}
