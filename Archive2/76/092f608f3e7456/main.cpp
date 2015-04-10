#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using boost::property_tree::ptree;
using boost::property_tree::read_json;
using boost::property_tree::write_json;

int main() {

    std::istringstream iss(R"({ "a" : { "middle" : { "a1":1, "a2":2, "a3":3 }, "more":"stuff" } })");
    ptree pt;
    read_json(iss, pt);

    auto& parent = pt.get_child("a");
    auto& middle = pt.get_child("a.middle");

    std::move(middle.begin(), middle.end(), back_inserter(parent));
    parent.erase("middle");

    write_json(std::cout, pt);

}
