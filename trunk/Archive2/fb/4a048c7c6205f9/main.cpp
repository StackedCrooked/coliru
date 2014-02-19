#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

using map_type = std::multimap< std::string, std::vector<std::string> > ;

void insert_first( std::istream& stm, map_type& map )
{
    std::string first, second ;
    while( std::getline( stm >> std::ws, first, ',' ) &&
           std::getline( stm >> std::ws, second ) ) map.emplace( first, std::vector<std::string>( 1, second ) ) ;
}

void insert_second( std::istream& stm, map_type& map )
{
    std::string first, second ;
    while( std::getline( stm >> std::ws, first, ',' ) &&
           std::getline( stm >> std::ws, second ) ) 
    {
        auto bounds = map.equal_range(first) ;
        
        if( bounds.first == bounds.second ) // not found, insert key and value
            map.emplace( first, std::vector<std::string>( 1, second ) ) ;
            
        else for( auto iter = bounds.first ; iter != bounds.second ; ++iter ) // found, append the value to all keys
            iter->second.push_back(second) ;
    }
}

int main()
{
    std::istringstream file1
    (
        "red, apple\n"
        "red, bird\n"
        "green, truck\n"
        "blue, car\n"
        "yellow, ball\n"
        "orange, candy\n"
    ) ;

    std::istringstream file2
    (
        "gold, necklace\n"
        "green, tree\n"
        "yellow, sticker\n"
        "blue, water\n"
        "red, bag\n"
    ) ;

    map_type map ;
    insert_first( file1, map ) ;
    insert_second( file2, map ) ;

    for( const auto& pair : map )
    {
        std::cout << pair.first  ;
        for( const std::string& s : pair.second ) std::cout << ", " << s  ;
        std::cout << '\n' ;
    }
}
