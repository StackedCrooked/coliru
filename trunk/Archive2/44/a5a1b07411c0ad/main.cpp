#include <boost/range/adaptors.hpp>
#include <boost/range/join.hpp>
#include <boost/range/algorithm.hpp>

using namespace boost::adaptors;
using boost::copy_range;

#include <iostream>

int main() {
    typedef std::vector<int> V;
    V const v { 1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14, 7, 15, 8, 16 };

    auto rearranged = copy_range<V>(join(v | strided(2), v | sliced(1, v.size()) | strided(2)));

    boost::copy(rearranged, std::ostream_iterator<int>(std::cout,";"));
}
