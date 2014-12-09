#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <iostream>

using namespace boost::property_tree;

std::string to_json_string(ptree const& pt)
{
    std::ostringstream oss;
    json_parser::write_json(oss, pt, false);
    return oss.str();
}

int main()
{
    ptree pt;
    ptree commands;

    pt.put<int>("mCommandID", 1);
    pt.put<int>("mTimeSent", 0);
    pt.put("commands", to_json_string(ptree {}));
    pt.put("more-commands", to_json_string(pt)); // a crude example

    json_parser::write_json(std::cout, pt);
}
