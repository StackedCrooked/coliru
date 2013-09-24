#include <map>
#include <utility>
#include <algorithm>
#include <iostream>

struct A {};

int main()
{
    A a;
    typedef std::map<std::pair<int, int>, struct A> myMap_t;
    myMap_t myMap;

    auto compare_first = [](
        myMap_t::value_type const & p1,
        myMap_t::value_type const & p2 )
    {
        return p1.first.first < p2.first.first;
    };
    
    myMap.insert(std::make_pair(std::pair<int, int>(1, 200), a));
    myMap.insert(std::make_pair(std::pair<int, int>(1, 202), a));
    myMap.insert(std::make_pair(std::pair<int, int>(2, 198), a));
    myMap.insert(std::make_pair(std::pair<int, int>(2, 207), a));

    for( auto it = myMap.begin(); it != myMap.end(); it = std::upper_bound( it, myMap.end(), *it, compare_first ) )
        std::cout << it->first.first << " " << it->first.second << "\n";
}
