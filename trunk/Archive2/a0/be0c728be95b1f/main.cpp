#include "boost/date_time.hpp"
#include <iostream>

using namespace boost::gregorian; 
using namespace boost::posix_time;

int main()
{
    uint64_t offset = uint64_t(113ul)*365ul*24ul*60ul*60ul*1000ul; // 113 years give or take some leap seconds/days etc.?

    static const ptime time_t_epoch(date(1901,1,1)); 
    std::cout << "epoch: " << time_t_epoch << "\n";

    ptime result = time_t_epoch + milliseconds(offset);
    std::cout << "final: " << result << "\n";
}