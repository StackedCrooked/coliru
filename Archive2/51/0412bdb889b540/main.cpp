#include <iostream>
#include <boost/icl/interval_map.hpp>
#include <boost/range/adaptor/map.hpp>
#include <boost/range/algorithm/max_element.hpp>
namespace icl = boost::icl;
namespace rng = boost::adaptors;
int main()
{
    icl::interval_map<int, int> party;

    party += make_pair( icl::interval<int>::right_open( 5,  8), 1);
    party += make_pair( icl::interval<int>::right_open( 3,  4), 1);
    party += make_pair( icl::interval<int>::right_open(13, 20), 1);
    party += make_pair( icl::interval<int>::right_open( 7, 10), 1);

    int max = *max_element(party | rng::map_values);
    std::cout << "max value = " << max << '\n' << "found in the interval(s) ";
    for(const auto& p : party)
        if(p.second == max)
            std::cout << p.first << ' ';
    std::cout << '\n';
}
