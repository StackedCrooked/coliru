#include <boost/date_time/posix_time/posix_time.hpp>
#include <iostream>

int main()
{    
	static std::locale loc(std::cout.getloc(), new boost::posix_time::time_facet("%Y-%m-%d %H:%M:%S"));
	
    const time_t timestamp = 1390220376;  // 2014-01-20 12:19:36 UTC
    
	std::cout.imbue(loc);
	std::cout << boost::posix_time::from_time_t(timestamp);
}