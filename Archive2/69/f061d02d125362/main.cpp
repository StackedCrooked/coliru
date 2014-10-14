#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <sstream>
#include <iostream>

using boost::property_tree::ptree;

int main()
{
    std::stringstream ss("<Clients>\n"
        "  <Client name=\"Alfred\" />\n"
        "  <Client name=\"Thomas\" />\n"
        "  <Client name=\"Mark\" />\n"
        "</Clients>");

    ptree pt;
    boost::property_tree::read_xml(ss, pt);

    for (auto& child : pt.get_child("Clients"))
    {
        if (child.first == "Client")
            std::cout << child.second.get<std::string>("<xmlattr>.name", "No name") << "\n";
    }
}
