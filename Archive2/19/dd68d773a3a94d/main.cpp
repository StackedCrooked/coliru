#include <iostream>
#include <boost/icl/interval_map.hpp>
#include <boost/icl/interval.hpp>

int main()
{
    boost::icl::interval_map<double, int> joined_map;
    using ival = boost::icl::interval<double>;

    joined_map.add({ival::open(1., 2.), 1});
    joined_map.add({ival::open(3., 5.), 2});
    std::cout << "#1: "; for (auto el : joined_map) std::cout << el.first << ": " << el.second << ", "; std::cout << "\n";

    joined_map.add({ival::open(4., 6.), 3});
    std::cout << "#2: "; for (auto el : joined_map) std::cout << el.first << ": " << el.second << ", "; std::cout << "\n";

    joined_map.subtract({ival::open(4., 6.), 3});
    std::cout << "#3: "; for (auto el : joined_map) std::cout << el.first << ": " << el.second << ", "; std::cout << "\n";

}
