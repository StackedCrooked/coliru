#include <iostream>
#include <boost/icl/interval_map.hpp>
#include <boost/range/adaptor/map.hpp>
#include <boost/range/algorithm/max_element.hpp>
namespace icl = boost::icl;
namespace rng = boost::adaptors;
int main()
{
    icl::discrete_interval<int> input[] = {{5,8}, {3,4}, {13,20}, {7,10}};
    icl::interval_map<int, int> party;
    for(auto& i : input)
       party += make_pair(i, 1);

    int max = *max_element(party | rng::map_values);
    std::cout << "max value = " << max << '\n' << "found in the interval(s) ";
    for(const auto& p : party)
        if(p.second == max)
            std::cout << p.first << ' ';
    std::cout << '\n';
}
