#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <functional>
#include <tuple>
#include <algorithm>

int main()
{
    const std::map< std::multiset<int>, std::map<int, int> > map =
    {
        { { 0, 1       },    { {0,18}, {1,13}, {5,14}, {6,12} } },
        { { 0, 1, 2    },    { {0,14}, {1,17}, {2,14}        }  },
        { { 1, 2       },    { {3,11}, {5,19}, {6,17}, {7,18} } },
        { { 1, 2, 3, 4 },    { {0,17}, {1,11}, {2,10},       } },
        { { 2, 3       },    { {7,16}, {8,13}, {9,13}        } }
    };

    // we don't want large numbers of copies of multisets
    using wrapped_multiset_type = std::reference_wrapper< const std::multiset<int> > ;

    using tuple_type = std::tuple< int /* value(map) */, int /* key(map) */, wrapped_multiset_type > ;
    std::vector< tuple_type > vec ;

    for( const auto& v : map )
    {
        for( const auto& pair : v.second )
             vec.push_back( std::make_tuple( pair.second, pair.first, std::cref(v.first) ) ) ;
    }

    const auto cmp = []( const tuple_type& a, const tuple_type& b ){ return std::get<0>(a) < std::get<0>(b) ; } ;
    std::sort( vec.begin(), vec.end(), cmp ) ;

    for( const auto& tup : vec )
    {
        std::cout << "map: { value " <<  std::get<0>(tup) << " key " << std::get<1>(tup) << " } " << "  multiset { " ;
        for( int v : std::get<2>(tup).get() ) std::cout << v << ' ' ;
        std::cout << " }\n" ;
    }
}
