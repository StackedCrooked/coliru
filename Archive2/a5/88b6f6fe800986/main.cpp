#include "/Archive2/c4/619c8a0b359daf/main.cpp" //time_facet.hpp
#include <boost/date_time/posix_time/posix_time.hpp>

int main()
{
    using namespace boost::posix_time;
    ptime const date_time = microsec_clock::local_time();

    std::cout << date_time << std::endl;

    auto facet = new time_facet("%Y-%b-%d %H:%M:%S%4 %z");
    std::cout.imbue(std::locale(std::cout.getloc(), facet));
    std::cout << date_time << std::endl;
}
