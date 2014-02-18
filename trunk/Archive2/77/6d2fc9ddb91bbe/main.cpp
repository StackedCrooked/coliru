#include <map>
#include <set>
#include <string>
#include <iostream>
#include <sstream>

// assumption: elininate duplicates; mapped_type is std::set<std::string>
// otherwise; mapped_type would be std::vector<std::string>

using map_type = std::map< std::string, std::set<std::string> > ;

void insert( std::istream& stm, map_type& map )
{
    std::string first, second ;
    while( std::getline( stm >> std::ws, first, ',' ) &&
           std::getline( stm >> std::ws, second ) ) map[first].insert(second) ;
}

int main()
{
    std::istringstream file1
    (
        "red, apple\n"
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
    insert( file1, map ) ;
    insert( file2, map ) ;

    for( const auto& pair : map )
    {
        std::cout << pair.first  ;
        for( const std::string& s : pair.second ) std::cout << ", " << s  ;
        std::cout << '\n' ;
    }
}
