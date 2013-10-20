#include <iostream>
#include <boost/date_time/local_time/local_time.hpp>

int main(){
    using namespace boost::local_time;
    using namespace boost::posix_time;

    ptime pt(not_a_date_time);

    std::stringstream ss("05/11/1996");

    // set format
    local_time_input_facet* input_facet = new local_time_input_facet();
    input_facet->format("%d/%m/%Y");
    ss.imbue(std::locale(ss.getloc(), input_facet));

    // parse
    if (ss >> pt)
    {
        std::cout << pt << std::endl;

        auto tm   = to_tm(pt);
        int year  = tm.tm_year;
        int month = tm.tm_mon + 1; // for 1-based (1:jan, .. 12:dec)
        int day   = tm.tm_mday;

        std::cout << "That's the " << day << "th of " << std::setw(2) << std::setfill('0') << month << " in the year " << year << "\n";
    }
}
