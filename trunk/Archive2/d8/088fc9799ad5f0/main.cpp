#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

namespace pt = boost::property_tree;

const std::string json = 
R("{
   "menu":
   {
      "foo": true,
      "bar": "true",
      "value": 102.3E+06,
      "popup":
      [
         {"value": "New", "onclick": "CreateNewDoc()"},
         {"value": "Open", "onclick": "OpenDoc()"},
      ]
   }
}");

int main()
{
    try
    {
        pt::ptree ptree;
        std::istringstream buf(json);
        
        pt::json_parser::read_json(buf, ptree);
    }
    catch(const std::exception& e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
        return -1;
    }
}
