#include <iostream>
#include <string>
#include <set>
#include <cctype>
#include <algorithm>
#include <sstream>

std::string make_key( std::string str )
{
    for( char& c : str ) c = std::tolower(c) ; // 2011

    // for( std::size_t i = 0 ; i < str.size() ; ++i ) // 1998
    //     str[i] = std::tolower( str[i] ) ;

    std::sort( str.begin(), str.end() ) ;
    return str ;
}

bool inserted( std::set<std::string>& anagram_set, const std::string& str )
{ return anagram_set.insert( make_key(str) ).second ; }

int main()
{
    std::istringstream input_file( "stack\n kcats\n stacka\n astack\n kcats\n overflow\n"
                                    "ooverflow\n overflowo\n Abc\n ABC\n" ) ;

    std::set<std::string> anagram_set ;

    std::string word ;
    while( input_file >> word )
        if( inserted(anagram_set,word) ) std::cout << word << '\n' ;
}
