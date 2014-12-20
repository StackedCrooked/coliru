#include <boost/date_time/gregorian/greg_date.hpp>
#include <boost/date_time/gregorian/gregorian_io.hpp>
#include <iostream>

using namespace boost;

namespace {
    struct day_proxy { unsigned short days; };
    day_proxy operator "" _d(unsigned long long v) { return { static_cast<unsigned short>(v) }; }
    
    struct mon_day_proxy { unsigned short months, days; };

    mon_day_proxy operator-(unsigned short months, day_proxy const& proxy) { return { months, proxy.days }; }
    gregorian::date operator-(unsigned short years, mon_day_proxy const& proxy) { return { years, proxy.months, proxy.days }; }
}

int main() {
    auto date1 = 2014-(12-18_d);
    auto date2 = 2014-(12-19_d);

    std::cout << date1 << ", " << date2 << "\n";
    (date1 < date2 ? date1 : date2) = gregorian::day_clock::local_day();
    std::cout << date1 << ", " << date2 << "\n";
}
