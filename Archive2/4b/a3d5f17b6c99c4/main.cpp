#include <iostream>
#include <type_traits>
#include <string>
#include <cctype>
#include <algorithm>
#include <iterator>

enum difficulty : unsigned int { EASY, MEDIUM, HARD, EXPERT, MASTER, HEROIC };

template < unsigned int N > struct level : std::integral_constant< unsigned int, level<N-1>::value * 10 > {};

template <> struct level<EASY> : std::integral_constant< unsigned int, 10 > {} ;

unsigned int level_of( difficulty d )
{
    switch(d)
    {
        case EASY: return level<EASY>::value ;
        case MEDIUM: return level<MEDIUM>::value ;
        case HARD: return level<HARD>::value ;
        case EXPERT: return level<EXPERT>::value ;
        case MASTER: return level<MASTER>::value ;
        default: return level<HEROIC>::value ;
    }
}

static constexpr const char* const difficulty_str[] = { "EASY", "MEDIUM", "HARD", "EXPERT", "MASTER", "HEROIC" };

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
            for( char& c : str ) c = std::toupper(c) ;
            const auto iter = std::find( std::begin(difficulty_str), std::end(difficulty_str), str ) ;
            if( iter != std::end(difficulty_str) ) d = difficulty( iter - std::begin(difficulty_str) ) ;
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
