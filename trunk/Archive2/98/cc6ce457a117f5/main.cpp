#include <boost/date_time/gregorian/greg_date.hpp>

boost::gregorian::date GetDateTime(int n)
{
  return boost::gregorian::date (2010,1,1) + boost::gregorian::days(n);
}

#include <boost/date_time/gregorian/gregorian_io.hpp>
#include <iostream>
int main() {
    std::cout << GetDateTime(42);
}
