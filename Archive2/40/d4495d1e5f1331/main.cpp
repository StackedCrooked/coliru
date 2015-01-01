#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>

boost::posix_time::ptime GetDateTime(int n)
{
  return boost::posix_time::ptime (boost::gregorian::date (2010,1,1) + boost::gregorian::days(n));
}

#include <iostream>
int main() {
    std::cout << GetDateTime(42);
}
