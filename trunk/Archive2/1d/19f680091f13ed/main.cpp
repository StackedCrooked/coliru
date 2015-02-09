#include <boost/date_time/posix_time/posix_time.hpp>
#include <iostream>
#include <sstream>

std::string FormatTime(boost::posix_time::ptime now)
{
  using namespace boost::posix_time;
  static std::locale loc(std::cout.getloc(),
                         new time_facet("%Y-%m-%d %H%M%S"));

  std::basic_stringstream<char> ss;
  ss.imbue(loc);
  ss << now << "." << now.time_of_day().fractional_seconds()/1000;
  return ss.str();
}

std::string IsoString(boost::posix_time::ptime now)
{
    return boost::posix_time::to_iso_string(now);
}

int main() {
    boost::posix_time::ptime now = boost::posix_time::microsec_clock::universal_time();
    std::cout << IsoString(now) << std::endl;
    std::cout << FormatTime(now) << std::endl;
}