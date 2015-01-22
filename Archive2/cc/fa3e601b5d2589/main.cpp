#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

std::vector< std::pair< int, std::string > > sorted_on_values( const std::map< std::string, int >& map )
{
    std::vector< std::pair< int, std::string > > result ;
    for( const auto& pair : map ) result.emplace_back( pair.second, pair.first ) ; // *** note: second,first

    std::sort( std::begin(result), std::end(result) ) ;
    return result ;
}

int main()
{
    const std::map< std::string, int > map { {"abc",7}, {"xyz",2}, {"ghi",5}, {"jkl",0}, {"def",2} } ;
    for( const auto vkpair : sorted_on_values(map) ) std::cout << vkpair.first << ' ' << vkpair.second << '\n' ;
}
