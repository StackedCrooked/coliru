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
    std::pair<vec_i, vec_d> temp;
    int i[] = {2, 3, 4};
    temp.first.assign(i, i+3);
    double d[] = {4.3, 5.1, 6.4};
    temp.second.assign(d, d+3);

    std::map<int, double> new_map;

    std::transform(temp.first.begin(), temp.first.end()
                 , temp.second.begin()
                 , std::inserter(new_map, new_map.begin())
                 , &std::make_pair<int, double>);

    for (std::map<int, double>::iterator it = new_map.begin(); it != new_map.end(); ++it)
    {
        std::cout << it->first << " : " << it->second << std::endl;
    }
}
