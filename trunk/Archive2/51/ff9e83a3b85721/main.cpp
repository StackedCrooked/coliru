#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include <fstream>
#include <iostream>

using namespace boost::property_tree;


void parse_tree(ptree& pt, std::string key)
{
    std::string nkey;
    auto settings = xml_parser::xml_writer_make_settings<std::string>('\t', 1);

    if (!key.empty()) {
        nkey = key + ".";
    }

    ptree::const_iterator end = pt.end();
    for(ptree::iterator it = pt.begin(); it != end; ++it)
    {
        //if the node's id an .html filname, save the node to file
        std::string id = it->second.get("<xmlattr>.id","");

        if (id.find(key) != std::string::npos) {
            // write the single element: (undocumented API)
            boost::property_tree::xml_parser::write_xml_element(
                    std::cout, it->first, it->second,
                    0, settings
                );

            // or: create a new pt with the single child
            std::cout << "\n==========================\n\n";
            ptree tmp;
            tmp.add_child(it->first, it->second);
            write_xml(std::cout, tmp, settings);
        }

        parse_tree(it->second, nkey + it->first); //recursion
    }
}

int main() {
    ptree pt;
    read_xml("input.txt", pt);

    parse_tree(pt, "B");
}
