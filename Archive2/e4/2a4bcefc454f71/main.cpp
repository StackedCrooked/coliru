#include <iostream>
#include <string>
#include <locale>

int main()
{
    std::string line ;
    const auto input_locale = std::cin.getloc() ;
    while( std::getline( std::cin, line ) )
    {
        for( char& c : line ) c = std::toupper( c, input_locale ) ;
        std::cout << line << '\n' ;
    }
}
