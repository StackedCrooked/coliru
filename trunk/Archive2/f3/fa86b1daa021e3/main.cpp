#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <iostream>
#include <locale>
using boost::property_tree::ptree;

int main()
{
    ptree xmlTree;
    read_xml("input.xml", xmlTree);

    auto xmlTreeChild = xmlTree.get_child("lot");

    for (auto it = xmlTreeChild.begin(); it != xmlTreeChild.end();)
    {
        std::string strItem = it->first.data();
        if (strcmp(strItem.c_str(), "item") == 0)
        {
            std::string strLabel = it->second.get_child("label").data();
            if (strcmp(strLabel.c_str(), "item3") != 0)
            {
                it = xmlTreeChild.erase(it);
            }
        }       
        ++it;
    }

    auto settings = boost::property_tree::xml_writer_make_settings<std::string>('\t', 1, "windows-1252");
    //std::cout.imbue(std::locale("en_US.iso8859-1"));
    write_xml(std::cout, xmlTree, settings);
}
