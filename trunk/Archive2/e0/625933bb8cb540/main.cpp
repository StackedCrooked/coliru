#include <iostream>
#include <boost/icl/interval_map.hpp>

namespace icl = boost::icl;

int main()
{
    icl::interval_map<double, int> joined_map;
    using ival = icl::interval<double>;

    joined_map.add({ival::open(1., 2.), 1});
    joined_map.add({ival::open(3., 5.), 2});
    std::cout << "#1: "; for(auto el : joined_map) std::cout << el.first << ": " << el.second << ", "; std::cout << "\n";

    joined_map.erase(ival::open(3., 6.));
    joined_map.add({ival::open(3., 6.), 4});
    std::cout << "#2: "; for(auto el : joined_map) std::cout << el.first << ": " << el.second << ", "; std::cout << "\n";
}
