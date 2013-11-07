#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <iostream>

using namespace boost::property_tree;


int main()
{
    ptree error;
    error.put("name", "ARPTimeout");
    error.put("value.ip", "1.1.1.1");
    error.put("value.retries", 10);
    error.put("value.time_waited", 60);
    
    write_xml("error.xml", error);
    
    write_json("error.json", error);
}