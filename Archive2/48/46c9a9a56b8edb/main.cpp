#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <sstream>
#include <iostream>
#include <boost/foreach.hpp>

struct sheet { int id; std::string info; };
static std::string const sample = "[{\"id\":\"1\",\"this\":\"that\"},{\"id\":\"2\",\"that\":\"this\"}]";

int main() {
    using namespace boost::property_tree;

    ptree pt;
    std::istringstream iss(sample);
    read_json(iss, pt);

    std::vector<sheet> sheets;
    BOOST_FOREACH(ptree::value_type e, pt)
    {
        std::string info = "(`this` not found)";
    
        boost::optional<ptree&> this_property = e.second.get_child_optional("this");
        if (this_property)
            info = this_property->get_value(info);

        sheet s;

        s.id   = e.second.get_child("id").get_value(-1);
        s.info = info;

        sheets.push_back(s);
    }

    BOOST_FOREACH(sheet s, sheets)
        std::cout << s.id << "\t" << s.info << "\n";
}
