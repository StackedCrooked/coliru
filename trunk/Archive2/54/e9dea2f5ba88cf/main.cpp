#include <boost/range/adaptor/map.hpp>
#include <map>
#include <vector>

#include <iostream>

int main()
{
    std::multimap<int, int> mm;
    mm.emplace(1, 1);
    mm.emplace(1, 2);
    mm.emplace(2, 3);
    mm.emplace(2, 4);
    
    for (auto e : mm)
        std::cout << e.first << " " << e.second << "\n";
        
    auto values = mm | boost::adaptors::map_values;
    std::vector<int> v(values.begin(), values.end());
    
    for (auto e : v)
        std::cout << e << " ";
}