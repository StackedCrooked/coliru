#include <boost/date_time.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <iostream>
#include <sstream>
#include <memory>


std::string get_curr_date() {
    auto date = boost::date_time::second_clock<boost::posix_time::ptime>::universal_time();

    //boost::posix_time::time_facet* facet = new boost::posix_time::time_facet("%a, %d %b %Y %H:%M:%S GMT");
    std::unique_ptr<boost::posix_time::time_facet> facet(new boost::posix_time::time_facet("%a, %d %b %Y %H:%M:%S GMT"));

    std::ostringstream os;
    os.imbue(std::locale(os.getloc(), facet.get()));
    os << date;

    return os.str();
}


int main() {
    std::cout << get_curr_date() << std::endl;
}