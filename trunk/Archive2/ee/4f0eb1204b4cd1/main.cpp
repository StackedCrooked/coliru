#include <boost/property_tree/info_parser.hpp>

using ptree = boost::property_tree::ptree;

int main()
{
    ptree pt;
    boost::property_tree::read_info(std::cin, pt);

    ptree entries = pt.get_child("entries");

    // create a new value
    ptree clone1 = pt.get_child("entries").begin()->second;
    clone1.add("i-was-here", 3.1416);
    clone1.put("name", "n3");

    // add the newvalue
    pt.add_child("entries.entry", clone1);

    boost::property_tree::write_info(std::cout, pt);
}
