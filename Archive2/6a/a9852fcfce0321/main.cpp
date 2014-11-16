#include <boost/icl/interval.hpp>
#include <boost/range/iterator_range.hpp>
#include <iostream>
#include <map>

namespace icl = boost::icl;

int main() {
    using Ival = icl::interval<int>::type;
    using Map  = std::map<Ival, int>;

    Map const m {
        Map::value_type {Ival::closed(1,3), 10},
        Map::value_type {Ival::closed(3,5), 6},
        Map::value_type {Ival::closed(1,8), 9},
        Map::value_type {Ival::closed(7,8), 15} 
    };

    for (auto e : m) std::cout << e.first << " -> " << e.second << "\n";

    std::cout << "------------------------------\n";

    for (auto e : m) 
        if (icl::contains(e.first, 3))
            std::cout << e.first << " -> " << e.second << "\n";
}

