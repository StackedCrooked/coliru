#include <boost/date_time/posix_time/posix_time.hpp>

int main()
{
    using namespace boost::posix_time;
    ptime const date_time = microsec_clock::local_time();

    std::cout << date_time << std::endl;

    auto facet = new time_facet("%Y-%b-%d %H:%M:%S%f %z");
    std::cout.imbue(std::locale(std::cout.getloc(), facet));
    std::cout << date_time << std::endl;
}
