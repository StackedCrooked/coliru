#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <iostream>

static std::string const sample = "{ \"Person1\" : { \"Name\" : \"Neha\", "
    "\"Gender\": \"Female\", \"City\" : \"Jamshedpur\", \"Status\":\"Married\" "
    "}, \"Person2\" : { \"Name\" : \"Gautam\", \"City\" : \"Banglore\", "
    "\"Status\": \"Single\" }, \"Person3\" : { \"Name\" : \"Tejaswini\", "
    "\"Gender\": \"Female\", \"City\" : \"Mysore\", \"Status\" : \"Single\" } }\n";

int main()
{
    using namespace boost::property_tree;
    std::istringstream iss(sample);
    ptree pt;
    read_json(iss, pt);

    BOOST_FOREACH(ptree::value_type & v, pt.get_child("Person1"))
    {
        std::cout << v.first.data() << ":" << v.second.data() << std::endl;
    }

    ptree const& person1 = pt.get_child("Person1");

    std::string Name   = person1.get<std::string>("Name");
    std::string Gender = person1.get<std::string>("Gender");
    std::string City   = person1.get<std::string>("City");
    std::string Status = person1.get<std::string>("Status");

    std::cout << "Or: [" << Name << ", " << Gender << ", " << City << ", " << Status << "]\n";
}
