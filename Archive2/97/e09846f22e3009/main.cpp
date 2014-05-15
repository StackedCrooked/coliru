#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/local_time/local_time.hpp>
#include <boost/date_time/local_time/local_time_io.hpp>

struct ymd_duration { int years, months, day; };

template <typename T>
T operator+(T const& pt, ymd_duration delta)
{
    using namespace boost::gregorian;
    return pt + years(delta.years) + months(delta.months) + days(delta.day);
}

time_t to_time_t(boost::posix_time::ptime const& pt) //! assumes UTC
{
    return (pt - boost::posix_time::from_time_t(0)).total_seconds();
}

int main()
{
    using namespace boost::local_time;

    auto now  = local_sec_clock::local_time(time_zone_ptr()),
         then = now + ymd_duration { 1, 3, -4 };

    std::cout << now  << ", " << to_time_t(now.utc_time())  << "\n";
    std::cout << then << ", " << to_time_t(then.utc_time()) << "\n";
}
