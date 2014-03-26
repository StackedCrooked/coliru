#include "boost/date_time/posix_time/time_formatters_limited.hpp"

using namespace boost::posix_time;

int main()
{
    ptime now = second_clock::local_time();
    std::cout << to_simple_string(now) << std::endl;
}