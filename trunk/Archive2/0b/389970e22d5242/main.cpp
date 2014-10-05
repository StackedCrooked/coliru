#include <iostream>
#include <sstream>
#include <string>
#include "boost/date_time.hpp"

namespace bt = boost::posix_time;

const std::locale formats[] = {
    std::locale(std::locale::classic(), new bt::time_input_facet("%d%m%Y %H:%M")), //25042014 23:59
    std::locale(std::locale::classic(), new bt::time_input_facet("%d%m%y %H:%M")), //250414 23:59
    std::locale(std::locale::classic(), new bt::time_input_facet("%d%m %H:%M")) //2504 23:59
    //additional formats removed for brevity
};
const size_t formats_n = sizeof(formats)/sizeof(formats[0]);

int main(void) {

    for (std::string input : {
            "25052014 12:45",
            "250514 12:45",
            "2505 12:45",
            })
    {
        bt::ptime dateTime;
        std::stringstream ss(input);

        for(size_t i = 0; i < formats_n; ++i) {
            ss.imbue(formats[i]);
            ss >> dateTime;
            if(dateTime != bt::not_a_date_time) {
                break;
            }
            ss.clear();
            ss.seekg(0);
        }

        std::cout << dateTime << std::endl;
    }
}
