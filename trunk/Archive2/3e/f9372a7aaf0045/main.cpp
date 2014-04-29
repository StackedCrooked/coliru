#include <boost/property_tree/detail/rapidxml.hpp>
#include <fstream>
#include <iomanip>
#include <iostream>
using namespace boost::property_tree::detail::rapidxml;

static void xmlTreePresent(xml_node<> const* node, int depth = 0) {
    if(node) {
        std::cout << std::setw(depth*2) << "" << node->name() << "\n";
        for(auto child = node->first_node(); child; child = child->next_sibling())
            if(child->name() && *child->name()) 
                xmlTreePresent(child, depth + 1);
    } else std::cout << std::setw(depth*2) << "" << "NULL NODE\n";
}

int main(int argc, char* argv[]) {
    std::ifstream ifs(argc>1? argv[1] : "input.txt");
    std::string xml(std::istreambuf_iterator<char>(ifs), {});

    try {
        xml_document<> doc;
        doc.parse<0>(&xml[0]);
        xmlTreePresent(doc.first_node());
    } catch(std::exception const& e) { 
        std::cerr << "ERROR: " << e.what() << "\n";
        return 1;
    } 
}
