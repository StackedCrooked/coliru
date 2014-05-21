#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>

int main() 
{
    using namespace boost::posix_time;
    ptime epoch = from_time_t(0);
    ptime other = time_from_string("2011-08-09 17:27:00.000000");
    std::cout << "diff is " << (other - epoch).total_microseconds() << std::endl;

    other = time_from_string("2011-08-09 17:27:00.00001");
    std::cout << "diff is " << (other - epoch).total_microseconds() << std::endl;
}
