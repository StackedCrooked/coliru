#include <boost/date_time/gregorian/greg_date.hpp>
#include <boost/date_time/gregorian/gregorian_io.hpp>
#include <iostream>

using namespace boost;

namespace {
    struct y_proxy { unsigned short years; };
    y_proxy operator "" _y(unsigned long long v) { return { static_cast<unsigned short>(v) }; }
    
    struct ym_proxy { unsigned short years, months; };

    ym_proxy operator-(y_proxy const& proxy, unsigned short months) { return { proxy.years, months }; }
    gregorian::date operator-(ym_proxy const& proxy, unsigned short days) { return { proxy.years, proxy.months, days }; }
}

int main() {
    auto d1 = 2014_y-12-18,
         d2 = 2014_y-12-19;

    std::cout << d1 << ", " << d2 << "\n";
    (d1 < d2 ? d1 : d2) = gregorian::day_clock::local_day();
    std::cout << d1 << ", " << d2 << "\n";
}
