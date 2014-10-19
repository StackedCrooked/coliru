#include <boost/date_time/gregorian/greg_date.hpp>
#include <boost/date_time/gregorian/gregorian_io.hpp>
#include <iostream>

using namespace boost::gregorian;

int main()
{
    date d(2014, 10, 17);
    static_assert(sizeof(d) == sizeof(int32_t), "truth");

    std::cout << d << "\n";

    uint32_t dn = d.day_number();
    dn += 1;

    gregorian_calendar::ymd_type ymd = gregorian_calendar::from_day_number(dn);
    d = { ymd.year, ymd.month, ymd.day };
    std::cout << d << "\n";
}
