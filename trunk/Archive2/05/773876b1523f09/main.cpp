#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

namespace pt = boost::property_tree;

const std::string json = "{\"title\":\"Foo\",\"items\":[{\"id\":123,\"name\":\"test1\"},{\"id\":456,\"name\":\"test2\"}]}";
int main()
{
    try
    {
        pt::ptree ptree;
        std::istringstream buf(json);
        
        pt::json_parser::read_json(buf, ptree);
        
        ptree.put("items", std::pair<std::string, int>("aa", 23));
        
        for(auto &v : ptree.get_child("items"))
        {
            std::cout << "id: "    << v.second.get<int>("id")
                      << " name: " << v.second.get<std::string>("name")
                      << std::endl;
        }
    }
    catch(const std::exception& e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
        return -1;
    }
}
