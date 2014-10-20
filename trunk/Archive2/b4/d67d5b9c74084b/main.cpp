#include <boost/regex.hpp>
#include <boost/algorithm/string_regex.hpp>

#include <string>
#include <iostream>

int main()
{
    std::string target_string = "Alyanae is securely locked in and Ken has taken the key.";
    boost::replace_all_regex(target_string, boost::regex("\\bken\\b", boost::regex::icase), std::string("This agent"), boost::match_flag_type::match_default);

    std::cout << target_string;
}
