#include <iostream>
#include <string>
#include <iterator>
#include <set>
#include <algorithm>

int main()
{
	const std::set<std::string> first { "omg", "hey", "there", "you" };
	const std::set<std::string> second { "hey", "look", "you", "guy" };

    std::set<std::string> third;
    // http://en.cppreference.com/w/cpp/iterator/inserter
	std::set_intersection( first.begin(), first.end(), second.begin(), second.end(), 
                           std::inserter( third, third.end() ) );
                           
    for( const std::string& str : third ) std::cout << str << ' ' ;
    std::cout << '\n' ;
    
    third.clear() ;
    std::set_union( first.begin(), first.end(), second.begin(), second.end(), 
                    std::inserter( third, third.end() ) ); 
                           
    for( const std::string& str : third ) std::cout << str << ' ' ;
    std::cout << '\n' ;
    
    third.clear() ;
    std::set_difference( first.begin(), first.end(), second.begin(), second.end(), 
                         std::inserter( third, third.end() ) );
                           
    for( const std::string& str : third ) std::cout << str << ' ' ;
    std::cout << '\n' ;
}