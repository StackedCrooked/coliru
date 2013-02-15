#include <boost/range.hpp>
#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm.hpp>
#include <algorithm>
#include <string>
#include <iostream>
#include <map>

using namespace boost;
using namespace boost::adaptors;

auto is_even = [](int n) { return n % 2 == 0; };
auto is_odd = [](int n) { return !is_even(n); };

int main()
{
    std::map<int, int> my_map;
    my_map[1] = 11;
    my_map[2] = 22;
    my_map[3] = 33;
    my_map[4] = 44;
    my_map[5] = 55;
    
    std::vector<int> target;
    copy(my_map | map_values | filtered(is_odd) | reversed, std::back_inserter(target));
    
    for (auto & t : target)
    {
        std::cout << t << std::endl;
    }
}