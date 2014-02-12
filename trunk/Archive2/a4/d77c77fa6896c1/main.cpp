#include <iostream>
#include <string>
#include <vector>

#include <map>
#include <utility>

using Map1 = std::map< int, std::vector<std::pair<int,int>>>;
using Map2 = std::map< std::pair<int,int>, int >;
using Map3 = std::map< int, int >;

Map3 foo( Map1 const & m1, Map2 const & m2 ) {
    auto m2end = m2.end(); // a constant call is move outside the loop
    Map3 result;
    for( auto & v1 : m1 ) { // each entry in m1 is made of the key as first and the value as second
        for( auto & p1 : v1.second ) { // iterate over the vector of pair
            auto v2it = m2.find( p1 ); // search for the pair
            if ( v2it != m2end ) {
                result[v1.first] += v2it->second; // if the pair was found, add the value for it to the result, using the map1 key as key
            }
        }
    }
    return result;
}

template<typename T,typename S>
std::ostream& operator<<(std::ostream& os, const std::pair<T,S>& pair )
{
    os << "{ " << pair.first << ", " << pair.second << " }";
    return os;
}
template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    os << "( ";
    for (auto& el : vec)
    {
        os << el << ", ";
    }
    os << " )";
    return os;
}

template<typename T,typename S>
std::ostream& operator<<(std::ostream& os, const std::map<T,S>& map)
{
    for (auto& el : map)
    {
        os << el.first << " : " << el.second << "\n";
    }
    return os;
}

int main()
{
    Map1 m1 { { 0, { {1,3}, {1,5}} }, { 1, { {2,1}, {2,4}} }, };
    Map2 m2 { { {1,3}, 4 }, { {1,5}, 3 }, { {2,1}, 1 }, { {2,4}, 5 }, };
    
    auto m3 = foo( m1, m2);
    
    std::cout << "m1 :\n" << m1 << std::endl;
    std::cout << "m2 :\n" << m2 << std::endl;
    std::cout << "m3 :\n" << m3 << std::endl;
}
