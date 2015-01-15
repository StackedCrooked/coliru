#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <sstream>

using namespace boost::property_tree;

std::string const sample = R"(
    {
        "schemaVersion": 1,
            "array": [{
            },
            {
                "id": "stackoverflow",
                "visible": true
            }]
    }
)";

int main() {

    ptree doc;
    std::istringstream iss(sample);
    read_json(iss, doc);

    BOOST_FOREACH(ptree::value_type & framePair2, doc.get_child("array")) {
        auto id = framePair2.second.get_optional<std::string>("id");
        if (id && !id->compare("stackoverflow")) {
            std::cout << framePair2.second.get<std::string>("id")      << std::endl;
            std::cout << framePair2.second.get<std::string>("visible") << std::endl;
            framePair2.second.put<std::string>("visible", "false");
            std::cout  << framePair2.second.get<std::string>("visible") << std::endl;
        }
    }

    write_json(std::cout, doc);
}
