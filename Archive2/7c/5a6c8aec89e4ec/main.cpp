#include <boost/date_time/gregorian/greg_date.hpp>
#include <boost/date_time/gregorian/gregorian_io.hpp>
#include <iostream>

int main()
{
    boost::gregorian::date const d(2005, 6, 25);
    boost::gregorian::date d2;

    std::stringstream oss;
    oss.imbue(std::locale(std::cout.getloc(), new boost::gregorian::date_facet("%Y %m %d")));

    oss << d; 

    oss.imbue(std::locale(std::cout.getloc(), new boost::gregorian::date_input_facet("%Y %m %d")));

    if (oss >> d2)
        std::cout << d2 << std::endl;
    else
        std::cout << "Not parsed\n";
}
