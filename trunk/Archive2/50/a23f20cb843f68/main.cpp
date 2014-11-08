#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <iostream>

using namespace boost::property_tree;

int main() {
    ptree pt;

    auto& list = pt.add_child("list", ptree{});

    for (auto data : { 12, 44, 23 })
        list.add("value", data)
                .add("<xmlattr>.active", true);

    xml_parser::write_xml(std::cout, pt);
}
