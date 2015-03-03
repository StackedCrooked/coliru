#include "boost/date_time/local_time/local_time.hpp"

int main()
{
  using namespace boost::gregorian;
  using namespace boost::local_time;
  using namespace boost::posix_time;

  time_zone_ptr tz_foo(new posix_time_zone("FOO"));
  ptime dt = ptime(date(2015, Mar, 2), hours(0));
  local_date_time local_dt = local_date_time(dt, tz_foo);
 
  std::cout << local_dt << std::endl;
  std::cout << "TZ UTC offset: " << tz_foo->base_utc_offset() << std::endl;
}