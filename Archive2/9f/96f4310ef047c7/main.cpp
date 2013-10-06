#include <string>
#include <iostream>
#include <fstream>
#include <limits>

int telRegels( std::ifstream& invoer )
{
    const char newline = '\n' ;

    int teller = 0 ; // *** initialize to zero

    char c ;
    while( invoer.get(c) )
    {
        if( c == newline ) ++teller ;
    }

    return teller ;
}

int telRegels_v2( std::ifstream& invoer )
{
    const char newline = '\n' ;
    int teller = 0 ;

    // http://www.cplusplus.com/reference/istream/istream/ignore/
    while( invoer.ignore( std::numeric_limits<std::streamsize>::max(), newline ) )
        ++teller ;

    return teller - 1 ;
}

int main()
{
    {
        std::ifstream this_file(__FILE__) ;
        std::cout << telRegels(this_file) << '\n' ;
    }

    {
        std::ifstream this_file(__FILE__) ;
        std::cout << telRegels_v2(this_file) << '\n' ;
    }
}
