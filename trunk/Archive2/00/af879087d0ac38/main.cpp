#include <thread>
#include <boost/date_time.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <iostream>

int main()
{
    using namespace boost::posix_time;

    auto const now      = second_clock::local_time(); 
    auto const today    = ptime(now.date());
    auto const leet     = time_duration(13,37,0);
    auto const deadline = now.time_of_day() >= leet
        ? ((today + time_duration(24,0,0)) + leet) 
        : (today + leet);

    while (true)
    {
        auto tod    = second_clock::local_time();

        std::cout << "\r" << (deadline - tod) << " remaining... " << std::flush;

        if (tod >= deadline)
            break;

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    std::cout << "\nLeet o'clock\n";
}
