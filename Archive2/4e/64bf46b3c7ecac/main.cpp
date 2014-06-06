#include <boost/regex.hpp>
#include <boost/algorithm/string_regex.hpp>

#include <string>
#include <iostream>

int main()
{
    boost::regex re("\\b(anonuuid|anon_id)\\b", boost::regex::icase);
    std::string target_string = "anonuuid final.device_anonuuid anon_id";

    std::string format = "QQQQ";
    boost::replace_all_regex(target_string, re, format, boost::match_flag_type::match_default);

    std::cout << target_string;
}
