#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <algorithm>
#include <iterator>
#include <boost/range/algorithm_ext/for_each.hpp>

typedef std::vector<int> vec_i;
typedef std::vector<double> vec_d;

int main()
{
    std::pair<vec_i, vec_d> temp = {{2, 3, 4}, {4.3, 5.1, 6.4}};
    
    std::map<int, double> new_map;

    boost::for_each(temp.first, temp.second, [&](int i, double d) { new_map[i] = d; });

    for (auto it = new_map.begin(); it != new_map.end(); ++it)
    {
        std::cout << it->first << " : " << it->second << std::endl;
    }
}
