#include <thread>
#include <boost/date_time.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <iostream>

int main()
{
    using namespace boost::posix_time;

    auto const leet = time_duration(13,37,0);

    while (true)
    {
        auto tod    = second_clock::local_time().time_of_day(); 
        auto remain = leet-tod;

        std::cout << "\r" << remain.minutes() << ':' << remain.seconds() << " remaining... " << std::flush;

        if (tod >= leet)
            break;

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    std::cout << "\nLeet o'clock\n";
}
