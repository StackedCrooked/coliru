#include <iostream>
#include <algorithm>
#include <string>
#include <cctype>

std::size_t countWs( char const* str )
{
    std::size_t c = 0;
    while (*str)
        c += !!std::isspace((unsigned char)*str++);
    return c;
}

std::string::size_type countWs( std::string const& str )
{
    return std::count_if( std::begin(str), std::end(str),
                          [] (unsigned char c) {return std::isspace(c);} );
}

int main()
{
    std::cout << countWs("A B C ") << '\n';
    std::cout << countWs(std::string("A B C "));
}