#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <tuple>
#include <algorithm>

int main()
{
    const std::map< std::multiset<int>, std::map<int, int> > map =
    {
        { { 0, 1       },    { {0,18}, {1,13}, {5,14}, {6,12} } },
        { { 0, 1, 2    },    { {0,14}, {1,17}, {2,14}         }  },
        { { 1, 2       },    { {3,11}, {5,19}, {6,17}, {7,18} } },
        { { 1, 2, 3, 4 },    { {0,17}, {1,11}, {2,10},        } },
        { { 2, 3       },    { {7,16}, {8,13}, {9,13}         } }
    };

    using tuple_type = std::tuple< int /* value(map) */, int /* key(map) */, std::multiset<int> > ;
    std::vector< tuple_type > vec ;

    for( const auto& v : map )
    {
        for( const auto& pair : v.second )
             vec.push_back( std::make_tuple( pair.second, pair.first,v.first ) ) ;
    }

    std::sort( vec.begin(), vec.end() ) ;

    for( const auto& tup : vec )
    {
        std::cout << "map: { value " <<  std::get<0>(tup) << " key " << std::get<1>(tup) << " } " << "  multiset { " ;
        for( int v : std::get<2>(tup) ) std::cout << v << ' ' ;
        std::cout << " }\n" ;
    }
}
