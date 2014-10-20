#include <boost/regex.hpp>
#include <boost/algorithm/string_regex.hpp>

#include <string>
#include <iostream>

int main()
{
    std::string test1 = "Liru is securely locked in and Ken has taken the key.", test2 = test1;
    std::string name("ken");
    std::string anonym("This agent");
    boost::ireplace_all(test1, name, anonym);
    boost::replace_all_regex(test2, boost::regex("\\b" + name + "\\b", boost::regex::icase), anonym, boost::match_flag_type::match_default); // Fix

    std::cout << test1 << '\n' << test2;
}
