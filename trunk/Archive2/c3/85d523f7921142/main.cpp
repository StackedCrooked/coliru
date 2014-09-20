#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <algorithm>
#include <iterator>

typedef std::vector<int> vec_i;
typedef std::vector<double> vec_d;

int main()
{
    std::pair<vec_i, vec_d> temp = {{2, 3, 4}, {4.3, 5.1, 6.4}};
    
    std::map<int, double> new_map;
                 
    std::transform(std::begin(temp.first), std::end(temp.first)
                 , std::begin(temp.second)
                 , std::inserter(new_map, std::begin(new_map))
                 , [] (int i, double d) { return std::make_pair(i, d); });

    for (auto it = new_map.begin(); it != new_map.end(); ++it)
    {
        std::cout << it->first << " : " << it->second << std::endl;
    }
}
