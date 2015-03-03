#include "boost/date_time/local_time/local_time.hpp"

int main()
{
  using namespace boost::gregorian;
  using namespace boost::local_time;
  using namespace boost::posix_time;

  boost::local_time::time_zone_ptr tz_foo(new boost::local_time::posix_time_zone("FOO"));
  ptime dt = ptime(date(2015, Mar, 2), hours(0));
  local_date_time local_dt = boost::local_time::local_date_time(dt, tz_foo);
 
  std::cout << "TZ: " << tz_utc->base_utc_offset() << std::endl;
  std::cout << local_dt << std::endl;
}