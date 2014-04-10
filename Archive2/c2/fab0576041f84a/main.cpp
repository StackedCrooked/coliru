#include <iostream>
#include <locale>
#include <string>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>

int main()
{
  const boost::posix_time::ptime time = 
      boost::posix_time::time_from_string("1981-08-20 08:05:00");

  // ptime to string.
  const std::string str_time = to_simple_string(time);
  std::cout << str_time << std::endl;

  // ptime to stringstream to string.
  std::stringstream stream;
  stream << time;
  std::cout << stream.str() << std::endl;
  stream.str("");

  // Use a facet to display time in a custom format (only hour and minutes).
  boost::posix_time::time_facet* facet = new boost::posix_time::time_facet();
  facet->format("%H:%M");
  stream.imbue(std::locale(std::locale::classic(), facet));
  stream << time;
  std::cout << stream.str() << std::endl;
}