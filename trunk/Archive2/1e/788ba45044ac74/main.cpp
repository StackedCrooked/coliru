#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm.hpp>
#include <iostream>

struct MixingParts{
    int intPart;
    double doublePart;
};

using boost::adaptors::transformed;

int main() {

    std::vector<MixingParts> v { { 1,0.1 }, {2, 0.2}, {3,0.3} };

    boost::copy(v | transformed(std::mem_fn(&MixingParts::intPart)),
            std::ostream_iterator<int>(std::cout, " "));
}
