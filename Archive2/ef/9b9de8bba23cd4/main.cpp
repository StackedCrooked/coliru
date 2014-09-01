#include <boost/range/adaptor/map.hpp>
#include <boost/range/algorithm/copy.hpp>
#include <map>
#include <vector>
#include <iterator>

#include <iostream>

int main()
{
    std::multimap<int, int> mm;
    mm.insert(std::make_pair(1, 1));
    mm.insert(std::make_pair(1, 2));
    mm.insert(std::make_pair(2, 3));
    mm.insert(std::make_pair(2, 4));
    
    for (std::multimap<int, int>::iterator it = mm.begin(), ite = mm.end(); it != ite; ++it)
        std::cout << it->first << " " << it->second << "\n";
    
    std::vector<int> v;
    v.reserve(mm.size());
    boost::copy(mm | boost::adaptors::map_values, std::back_inserter(v));
    
    boost::copy(v, std::ostream_iterator<int>(std::cout, " "));
}
