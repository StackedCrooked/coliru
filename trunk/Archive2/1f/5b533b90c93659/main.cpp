#include <iostream>
#include "boost/date_time.hpp"
#include "boost/date_time/posix_time/posix_time_io.hpp"

using namespace boost::posix_time;

boost::posix_time::ptime make(int h, int m, int s)
{
   return boost::posix_time::ptime
      (boost::gregorian::date(1900,1,1),
      boost::posix_time::time_duration(h,m,s,0));
}

int main()
{
   boost::posix_time::ptime t = make(22,2,0);
   std::cout << "made: " << t << "\n";

   int extra_mins = t.time_of_day().minutes() % 5;
   std::cout << "extra_mins: " << extra_mins << "\n";

   t -= boost::posix_time::minutes(extra_mins);
   std::cout << "t - extra_mins: " << t << "\n";

   if (t.time_of_day().minutes() != 0)
      std::cout << "ERROR";
}
