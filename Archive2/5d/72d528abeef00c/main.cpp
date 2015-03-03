#include "boost/date_time/local_time/local_time.hpp"
#include <iostream>

int main()
{
    using namespace boost::gregorian;
	using namespace boost::local_time;
	using namespace boost::posix_time;

	ptime dt = ptime(date(2015, Mar, 2), hours(0));
	time_zone_ptr tz_cet(new boost::local_time::posix_time_zone("CET+01:00:00"));
	local_date_time local_dt = boost::local_time::local_date_time(dt, tz_cet);

	std::cout << local_dt << std::endl;
	std::cout << local_dt.utc_time() << std::endl;

	time_zone_ptr tz_utc(new boost::local_time::posix_time_zone("UTC"));
	std::cout << local_dt.local_time_in(tz_utc) << std::endl;
}
