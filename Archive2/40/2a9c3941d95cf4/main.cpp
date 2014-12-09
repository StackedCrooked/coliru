#include <sstream>
#include <iostream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

using namespace boost::property_tree;

int main() {
    ptree pt;

    std::istringstream iss("<Parameter name=\"box\" />");
    xml_parser::read_xml(iss, pt);

    for (auto& element : pt)
    {
        std::cout << "'" << element.first << "'\n";
        for (auto& attr : element.second)
        {
            std::cout << "'" << attr.first << "'\n";
            for (auto& which : attr.second)
            {
                std::cout << "'" << which.first << "': \"" << which.second.get_value<std::string>() << "\"\n";
            }
        }
    }
}