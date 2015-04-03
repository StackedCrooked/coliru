#include <iostream>
#include <vector>
#include <map>

int main()
{
    const std::map< int, std::vector<double> > map =
    {
        { 247, { 1.2, 2.3, 3.4, 4.5 } },
        { 106, { 5.6, 6.7, 7.8, 8.9, 9.1, 1.2, 2.3 } },
        { 184, { 3.4, 4.5 } }
    };

    {
        // option 1: range-based loops
        for( const auto& pair : map )
        {
            std::cout << "key: " << pair.first << "  value: [  " ;
            for( double d : pair.second ) std::cout << d << "  " ;
            std::cout << "]\n" ;
        }
    }
    std::cout << "----------------\n" ;
    {
        // option 2: iterators
        for( auto map_iter = map.cbegin() ; map_iter != map.cend() ; ++map_iter )
        {
            std::cout << "key: " << map_iter->first << "  value: [  " ;
            for( auto vec_iter = map_iter->second.begin() ; vec_iter != map_iter->second.end() ; ++vec_iter )
                std::cout << *vec_iter << "  " ;
            std::cout << "]\n" ;
        }
    }
    std::cout << "----------------\n" ;
    {
        // option 3: range-based loop for map, subscript operator for vector
        for( const auto& pair : map )
        {
            std::cout << "key: " << pair.first << "  value: [  " ;
            for( std::size_t i = 0 ; i < pair.second.size() ; ++i )  std::cout << pair.second[i] << "  " ;
            std::cout << "]\n" ;
        }
    }
    
    // options 4, 5 ...
}
