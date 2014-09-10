#include <iostream>
#include <boost/date_time.hpp>
namespace bpt = boost::posix_time;
int main()
{
    std::cout.imbue(std::locale(std::locale(),
                    new bpt::time_facet("%a %b %d %I:%M:%S %p")));
    std::cout << bpt::second_clock::local_time() << '\n';
}
