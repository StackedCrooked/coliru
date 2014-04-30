#include <boost/property_tree/detail/rapidxml.hpp>
#include <fstream>
#include <iostream>
static void xmlTreePresent(boost::property_tree::detail::rapidxml::xml_node<> const* node, std::string indent = "") {
    if(node) {
        std::cout << indent << node->name() << "\n";
        for(auto child = node->first_node(); child; child = child->next_sibling())
            if(child->name() && *child->name()) xmlTreePresent(child, indent + "  ");
    } else std::cout << indent << "NULL NODE\n";
}
int main(int argc, char* argv[]) {
    std::string xml(std::istreambuf_iterator<char>(std::ifstream(argc>1? argv[1] : "input.txt").rdbuf()), {});
    boost::property_tree::detail::rapidxml::xml_document<> doc;
    xmlTreePresent((doc.parse<0>(&xml[0]), doc.first_node()));
}
