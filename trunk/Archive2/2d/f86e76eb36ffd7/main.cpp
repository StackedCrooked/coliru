#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/chrono.hpp>
#include <string>
#include <iostream>

int main()
{
    boost::posix_time::ptime const time_epoch(boost::gregorian::date(1970, 1, 1));

    auto ms = (boost::posix_time::second_clock::local_time() - time_epoch).total_microseconds();
    std::cout << "microseconds: " << ms << "\n";

    boost::posix_time::ptime now = time_epoch + boost::posix_time::microseconds(ms);
    std::cout << boost::posix_time::to_iso_string(now);
}
