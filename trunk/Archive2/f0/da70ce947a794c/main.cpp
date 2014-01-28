#include <iostream>
#include <string>
#include <cctype>

int main()
{
    const std::string look_up = "abcdefghijklmnopqrstuvwxyz0123456789" ;

    for( char c : "lower and UPPER CASE too #12689" )
    {
        if( std::isalnum(c) )
            std::cout << c << " => " << look_up.find( std::tolower(c) ) << '\n' ;
    }
}
