#include <boost/icl/split_interval_set.hpp>
#include <iostream>

namespace icl = boost::icl;

int main()
{
    icl::split_interval_set<int> intervals;
    intervals.insert({0, 10});
    intervals.insert({8, 14});

    for(auto r : intervals)
        std::cout << r;
}
