#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>

enum difficulty  { EASY, MEDIUM, HARD, EXPERT, MASTER, HEROIC };
const char* const difficulty_str[] = { "EASY", "MEDIUM", "HARD", "EXPERT", "MASTER", "HEROIC" };
const int difficulty_level[] = { 10, 100, 1000, 10000, 100000, 1000000 };

int level_of( difficulty d ) { return difficulty_level[d] ; }

std::ostream& operator<< ( std::ostream& stm, difficulty d )
{ return stm << difficulty_str[d] << '(' << level_of(d) << ')' ; }

std::istream& operator>> ( std::istream& stm, difficulty& d )
{
    unsigned int number ;
    if( stm >> number )
    {
        if( number <= HEROIC ) d = difficulty(number) ;
        else stm.setstate( std::ios::failbit ) ;
    }
    else
    {
        stm.clear() ;
        std::string str ;
        if( stm >> str )
        {
            for( std::size_t i = 0 ; i < str.size() ; ++i ) str[i] = std::toupper( str[i] ) ;
            
            const char* const* const iter = std::find( difficulty_str, difficulty_str+HEROIC, str ) ;
            if( iter != (difficulty_str+HEROIC) ) d = difficulty( iter - difficulty_str ) ;
            else stm.setstate( std::ios::failbit ) ;
        }
    }
    return stm ;
}

int main()
{
    std::cout << EXPERT << '\n' ; // EXPERT(10000)

    difficulty d ;
    if( std::cin >> d ) std::cout << d << '\n' ;
    if( std::cin >> d ) std::cout << d << '\n' ;
    if( std::cin >> d ) std::cout << d << '\n' ;

    if( std::cin >> d ) std::cout << d << '\n' ;
    else std::cerr << "*** error ***\n" ;
}
