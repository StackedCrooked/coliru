#include <iostream>
#include <sstream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

using boost::property_tree::ptree;
using boost::property_tree::xml_writer_make_settings;

int main()
{
    
    std::istringstream xml_in(
"<?xml version=\"1.0\" encoding=\"utf-8\"?>" 
"<list>" 
    "<object name=\"ob1\">"
        "<property1>foo</property1>"
    "</object>"
    "<object name=\"ob2\">"
        "<property1>bar</property1>"
    "</object>"
"</list>"
);
    
    ptree tree;
    read_xml(xml_in, tree);
    
    ptree &list = tree.get_child("list");
    ptree ob3;
    ob3.put("<xmlattr>.name","ob3");
    ob3.put("property1","baz");
    list.add_child("object",ob3);

    write_xml(std::cout, tree, xml_writer_make_settings(' ', 4));
    
}