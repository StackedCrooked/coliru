#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

int main()
{
    std::string a = "!!eix!@#$%fghjk^&*()_+%if***" ;
    std::cout << a << '\n' ;

    a.erase( std::remove_if( a.begin(), a.end(), []( char c ) { return std::ispunct(c); } ), a.end() ) ;
	std::cout << a << '\n' ;
}
