#include <boost/property_tree/ini_parser.hpp>
#include <iostream>

static std::string inidata =
R"(
    # comment

    [SECTION1]  
    key1 = 15
    key2=val  # woah       
    k#ey3=whoops
)";

using boost::property_tree::ptree;

void read_data(std::istream &is)
{

    ptree pt;
    read_ini(is, pt);

    for (auto section : pt)
        for (auto key : section.second)
            std::cout << "DEBUG: " << key.first << "=" << key.second.get_value<std::string>() << "\n";
}

#include <sstream>

int main()
{
    std::istringstream iss(inidata);
    read_data(iss);
}
