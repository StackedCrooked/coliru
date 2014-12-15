#include <boost/date_time/posix_time/posix_time_duration.hpp>
#include <iostream>
using DATE = double;

int main() {
    boost::posix_time::time_duration duration(1007645, 15, 0);

    DATE date = duration.total_milliseconds() / 1000.0 / 60 / 60 / 24;
    std::cout << date;
}
