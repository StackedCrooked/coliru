#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <sstream>
#include <iostream>

static std::string const sample = R"([{"id":"1","this":"that"},{"id":"2","that":"this"}])";

int main() {
    using namespace boost::property_tree;

    ptree pt;
    struct sheet { int id; std::string info; };

    std::istringstream iss(sample);
    read_json(iss, pt);

    std::vector<sheet> sheets;
    for(auto& e : pt)
    {
        std::string info = "(`this` not found)";
    
        auto this_property = e.second.get_child_optional("this");
        if (this_property)
            info = this_property->get_value(info);

        sheets.push_back(sheet {
            e.second.get_child("id").get_value(-1),
            info
        });
    }

    for(auto s : sheets)
        std::cout << s.id << "\t" << s.info << "\n";
}
