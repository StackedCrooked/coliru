#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_duration.hpp>
#include <iostream>
using DATE = double;

boost::posix_time::ptime pTime_from_DATE(double date)
{
    static const boost::posix_time::ptime::date_type base_date(1899, boost::gregorian::Dec, 30);
    return boost::posix_time::ptime(
            base_date, 
            boost::posix_time::milliseconds(date * 1000 * 60 * 60 * 24));
}

int main() {
    boost::posix_time::time_duration duration(1007645, 15, 0);

    DATE date = duration.total_milliseconds() / 1000.0 / 60 / 60 / 24;

    std::cout << date << ": " << pTime_from_DATE(date);
}
