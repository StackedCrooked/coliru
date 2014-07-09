#include <iostream>
#include <vector>
#include <unordered_map>

int main()
{
    const std::vector<int> a { 2, 234, 45, 99, 7, 8, 200 } ; // 99 is not present in b

    const std::vector<int> b { 8, 2, 45, 200, 7, 234 } ; //
    std::unordered_map< int, std::size_t > pos_map ; // map value in b to their positions
    for( std::size_t i = 0 ; i < b.size() ; ++i ) pos_map.emplace( b[i], i ) ; // O(N) time, O(N) space

    constexpr std::size_t npos = -1U ; // npos => invalid position
    std::vector<std::size_t> Location( a.size(), npos ) ;  // npos => value is not present in b
    for( std::size_t i = 0 ; i < a.size() ; ++i  ) // O(N)
    {
        const auto iter = pos_map.find( a[i] ) ; // look up its position in b - O(1)
        if( iter != pos_map.end() ) Location[i] = iter->second ; // if the value is in b
    }

    for( std::size_t pos : Location )
    {
        if( pos != npos ) std::cout << pos << ' ' ;
        else std::cout << "npos " ;
    }
    std::cout << '\n' ;
}
