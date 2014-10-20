#include <boost/regex.hpp>
#include <boost/algorithm/string_regex.hpp>

#include <string>
#include <iostream>

int main()
{
    std::string target_string = "Alyanae is securely locked in and This agent has taken the key.";
    boost::replace_all_regex(target_string, boost::regex("\\bken\\b", boost::regex::icase), std::string("QQQQ"), boost::match_flag_type::match_default);

    std::cout << target_string;
}
