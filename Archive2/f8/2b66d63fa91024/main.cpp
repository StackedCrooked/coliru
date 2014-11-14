#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <iostream>

using namespace boost::property_tree;

int main()
{
    std::istringstream iss(R"([
    {
        "ID": "cc7c3e83-9b94-4fb2-aaa3-9da458c976f7",
        "Type": "VM"
    }
    ])");

    ptree pt;
    json_parser::read_json(iss, pt);

    for (auto& array_element : pt) {
        for (auto& property : array_element.second) {
            std::cout << property.first << " = " << property.second.get_value<std::string>() << "\n";
        }
    }
}
