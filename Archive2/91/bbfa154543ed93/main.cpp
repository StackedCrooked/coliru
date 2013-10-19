#include <iostream>
#include <fstream>
#include <cctype>

int main()
{
    std::ifstream file( __FILE__ ) ; // this source file

    int upper = 0 ;
    int lower = 0 ;
    int digit = 0 ;
    int whitespace = 0 ;
    int punct = 0 ;
    int other = 0 ;

    char c ;
    while( file.get(c) ) // reads every byte including white spaces
    {
        if( std::isupper(c) ) ++upper ;
        else if( std::islower(c) ) ++lower ;
        else if( std::isdigit(c) ) ++digit ;
        else if( std::isspace(c) ) ++whitespace ;
        else if( std::ispunct(c) ) ++punct ;
        else ++other ;
    }

    std::cout << "upper: " << upper << '\n' // 'A' 'B' ...
               << "lower: " << lower << '\n' // 'a' 'b' ...
               << "digit: " << digit << '\n' // '0' '1' ...
               << "space: " << whitespace << '\n' // ' ' '\n' ...
               << "punct: " << punct << '\n' // '?' '.' ...
               << "other: " << other << '\n' ; // '©' '¶' '½' 
}
