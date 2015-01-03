#include <iostream>
#include <string>
#include <regex>
#include <set>

bool has_duplicates( std::string str )
{
    static const std::regex re( "[0-9]{1,2}" /* one or two decimal digits */
                                "[^0-9]" /* followed by a character that is not a decimal digit */  ) ;

    std::set<std::string> tokens ;

    // http://en.cppreference.com/w/cpp/regex/regex_token_iterator
    using iterator = std::sregex_token_iterator ;
    for( iterator iter( std::begin(str), std::end(str), re ) ; iter != iterator() ; ++iter )
    {
        // http://en.cppreference.com/w/cpp/container/set/insert
        if( !( tokens.insert( *iter ).second ) ) return true ; // found a duplicate
    }

    return false ; // did not find any duplicates
}

int main()
{
    for( std::string str : { "12b2c69z77m", "12b2c69z12b77m" } )
        std::cout << '"' << str << "\" has duplicates? " << std::boolalpha << has_duplicates(str) << '\n' ;
}
