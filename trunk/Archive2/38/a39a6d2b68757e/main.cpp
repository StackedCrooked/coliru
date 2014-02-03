#include <iostream>
#include <string>
#include <sstream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

int main()
{
    std::istringstream iss(R"(<?xml version="1.0" encoding="utf-8"?>
<tokens title="issues"></tokens>)");

    using boost::property_tree::ptree;
    ptree pt;
    read_xml(iss,pt);
    
    ptree& tokens_attrs = pt.get_child("tokens.<xmlattr>");
    std::cout << tokens_attrs.erase("title") << std::endl;
    
    //ptree& tokens = pt.get_child("tokens");
    //std::cout << tokens.erase("<xmlattr>") << std::endl;
    
    write_xml(std::cout,pt);

    return 0;
}


