#include <boost/date_time.hpp>

#include <iostream>
#include <locale>
#include <sstream>
#include <string>

std::string get_current_date_time(const char* fmt)
{
  const boost::local_time::time_zone_ptr utc_time_zone(new boost::local_time::posix_time_zone("GMT"));
  boost::local_time::local_time_facet* facet = new boost::local_time::local_time_facet(fmt);

  const boost::posix_time::ptime& my_ptime = boost::posix_time::second_clock::universal_time();
  boost::local_time::local_date_time now(my_ptime, utc_time_zone);

  std::ostringstream date_osstr;
  date_osstr.imbue(std::locale(date_osstr.getloc(), facet));
  date_osstr << now;

  return date_osstr.str();
}

int main()
{
  std::cout << get_current_date_time("%e %b %Y %T %q") << '\n';
}