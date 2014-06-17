#include </Archive2/a7/12ae60f0aa89dd/pugixml.hpp>
#include <iostream>

int main()
{
    pugi::xml_document doc;
    doc.load_file("input.txt");

    for (auto& to_remove : doc.select_nodes("descendant-or-self::to_remove/.."))
        while (to_remove.node().remove_child("to_remove"));

    doc.save(std::cout);
}
