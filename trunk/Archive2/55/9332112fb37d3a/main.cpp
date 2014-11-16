#include <boost/icl/split_interval_map.hpp>
#include <boost/range/iterator_range.hpp>
#include <iostream>

namespace icl = boost::icl;

int main() {
    using Map  = icl::split_interval_map<int, int>;
    using Ival = Map::interval_type;
    Map m;
    m.add({Ival::closed(1,3), 10});
    m.add({Ival::closed(3,5), 6});
    m.add({Ival::closed(1,8), 9});
    m.add({Ival::closed(7,8), 15});

    for (auto e : m) std::cout << e.first << " -> " << e.second << "\n";

    std::cout << "------------------------------\n";

    for (auto e : boost::make_iterator_range(m.equal_range(Ival::closed(3,3))))
        std::cout << e.first << " -> " << e.second << "\n";
}

