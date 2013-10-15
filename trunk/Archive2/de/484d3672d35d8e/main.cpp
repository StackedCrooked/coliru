#include <boost/date_time.hpp>
#include <boost/date_time/time_clock.hpp>
#include <iostream>

#include <thread>
#include <chrono>

int main()
{
    using namespace boost::gregorian;
    using boost::posix_time::ptime;
    using clock = boost::posix_time::microsec_clock; // or: boost::posix_time::second_clock;

    auto today       = date(day_clock::local_day());
    auto at_sunday   = greg_weekday(Sunday);
    auto next_sunday = next_weekday(today, at_sunday);

    auto duration = (ptime(next_sunday) - clock::local_time()).total_milliseconds();
    auto msecs    = duration.total_milliseconds();
    std::cout << msecs << "\n";

    std::this_thread::sleep_for(std::chrono::milliseconds(msecs));
}
