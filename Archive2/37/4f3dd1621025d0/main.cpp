#include "boost/date_time.hpp"
#include <iostream>

using namespace boost::gregorian; 
using namespace boost::posix_time;

int main()
{
    uint64_t offset = 113ul*365ul*24ul*60ul*60ul; // 113 years give or take some leap seconds/days etc.?

    static const ptime time_t_epoch(date(1901,1,1)); 
    static const uint32_t max_long = std::numeric_limits<int32_t>::max();
    std::cout << "epoch: " << time_t_epoch << "\n";

    ptime accum = time_t_epoch;
    while (offset > max_long)
    {
        accum  += seconds(max_long);
        offset -= max_long;
        std::cout << "accumulating: " << accum << "\n";
    }

    accum += seconds(offset);
    std::cout << "final: " << accum << "\n";
}
