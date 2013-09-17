#include <iostream>
#include <boost/date_time.hpp>

int main()
{
    using namespace boost::gregorian;
    date d(2013,Sep,13);
    std::cout << d << '\n';
    d -= days(1);
    std::cout << d << '\n';
}