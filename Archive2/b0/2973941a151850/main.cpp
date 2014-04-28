#include <boost/date_time.hpp>
#include <boost/date_time/local_time/local_time.hpp>

#include <iostream>
#include <locale>
#include <sstream>

using namespace boost;
static local_time::time_zone_ptr const utc_time_zone(new local_time::posix_time_zone("GMT"));

int main()
{
    local_time::local_time_facet* facet = new local_time::local_time_facet("%e %b %Y %T %q");

    posix_time::ptime my_ptime = posix_time::second_clock::universal_time();
    local_time::local_date_time now(my_ptime, utc_time_zone);

    std::ostringstream date_osstr;
    date_osstr.imbue(std::locale(date_osstr.getloc(), facet));
    date_osstr << now;

    std::cout << date_osstr.str() << '\n';
}
