#include <iostream>
#include <vector>
#include <map>

std::vector<int> mode( const std::vector<int>& input )
{
    if( input.empty() ) return {} ;

    std::map< int, int > frequency_map ;
    for( int i : input ) ++frequency_map[i] ;

    std::map< int, std::vector<int>, std::greater<int> > reverse_frequency_map ;
    for( const auto& pair : frequency_map )
        reverse_frequency_map[pair.second].push_back(pair.first) ;

    return reverse_frequency_map.begin()->second ;
}

int main()
{
   for( int v : mode( { 7, 1, 2, 6, 3, 2, 7, 7, 6, 3, 4, 5, 2, 4, 3, 1, 6, 7, 2, 3 } ) )
       std::cout << v << ' ' ;
   std::cout << '\n' ;
}
