#include <boost/date_time/gregorian/greg_date.hpp>
#include <boost/date_time/gregorian/gregorian_io.hpp>
#include <iostream>

using namespace boost;

int main() {
    gregorian::date date1(2014, 12, 18);
    gregorian::date date2(2014, 12, 19);

    std::cout << date1 << ", " << date2 << "\n";
    (date1 < date2 ? date1 : date2) = gregorian::day_clock::local_day();
    std::cout << date1 << ", " << date2 << "\n";
}
