#include <boost/date_time/gregorian/greg_date.hpp>
#include <boost/date_time/gregorian_calendar.hpp>
#include <boost/date_time/gregorian/formatters.hpp>
#include <boost/date_time/gregorian/gregorian_io.hpp>
#include <sstream>
#include <iostream>



int main()
{
    boost::gregorian::date d(2005, 6, 25);

    std::string s;
    {
        std::ostringstream oss;
        boost::gregorian::date_facet* facet(new boost::gregorian::date_facet("%Y %m %d"));
        oss.imbue(std::locale(std::cout.getloc(), facet));

        oss << d; 
        s = oss.str(); // s = "2005 06 25"
    }

    std::cout << "Output: '" << s << "'\n";
    {
        std::istringstream iss(s);
        iss.imbue(std::locale(std::cout.getloc(), new boost::gregorian::date_input_facet("%Y %m %d")));

        boost::gregorian::date d2;
        if (iss >> d2)
            std::cout << d2 << std::endl;
        else
            std::cout << "Not parsed\n";
    }
}
