#include <iostream>
#include <algorithm>
#include <string>

int main ()
{
    std::string words[] =
    {   "We", "all", "live", "in", "a", "yellow", "submarine", "\n",
        "yellow", "submarine,", "yellow", "submarine", "\n",
    };

    const std::size_t N = sizeof(words) / sizeof( words[0] ) ;

    for( const std::string& str : words ) std::cout << ' ' << str ;

    std::cout << "-----------------------------------\n" ;

    const std::string yellow = "yellow" ;
    const std::string lavender = "lavender" ;

    ///////////////////////////////////////////////////////////////////////////
    // replace strings in a sequence of strings: std::replace
    ///////////////////////////////////////////////////////////////////////////

    std::replace( words, words+N, yellow, lavender ) ;

    for( const std::string& str : words ) std::cout << ' ' << str ;


    std::cout << "-----------------------------------\n" ;

    std::string str = "We all live in a yellow submarine\n"
                       "yellow submarine, yellow submarine" ;
    std::cout << str << '\n' ;

    std::cout << "-----------------------------------\n" ;

    ///////////////////////////////////////////////////////////////////////////
    // replace substrings in a string: std::string::replace()
    ///////////////////////////////////////////////////////////////////////////

    for( std::size_t pos = str.find(yellow) ; pos != std::string::npos ; pos = str.find(yellow) )
        str.replace( pos, yellow.size(), lavender ) ;
    std::cout << str << '\n' ;

}
