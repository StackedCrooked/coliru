#include <sstream>
#include <iostream>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>

const std::string xml_str =
        "<foo>"
            "<bar param1=\"val1\" param2=\"val2\">"
                "<one>some text</one>"
                "<two>some text</two>"
            "</bar>"
            "<bar param1=\"val3\" param2=\"val4\">"
                "<one>more text</one>"
                "<two>more text</two>"
            "</bar>"
        "</foo>";

int main()
{
    using namespace boost::property_tree;
    using namespace boost::property_tree::xml_parser;

    std::istringstream iss(xml_str);
    ptree pt;
    read_xml(iss, pt);

    BOOST_FOREACH(ptree::value_type const& bar, pt.get_child("foo")) 
    {
         std::ostringstream oss;
         ptree tree;
         tree.push_back(bar);
         write_xml(oss, tree);
         std::cout << oss.str() << std::endl;
    }

    return 0;
}