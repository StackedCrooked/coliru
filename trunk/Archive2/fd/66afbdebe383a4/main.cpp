#include "boost/date_time/local_time/local_time.hpp"

int main()
{
  boost::local_time::time_zone_ptr tz_cet(new boost::local_time::posix_time_zone("CET"));
  boost::local_time::time_zone_ptr tz_utc(new boost::local_time::posix_time_zone("UTC"));
  std::cout << "CET TZ: " << tz_cet->base_utc_offset() << std::endl;
  std::cout << "UTC TZ: " << tz_utc->base_utc_offset() << std::endl;
}