#include <fstream>
#include <iostream>
#include <iomanip>
#include <boost/property_tree/detail/rapidxml.hpp>

using namespace boost::property_tree::detail::rapidxml;

static void xmlTreePresent(xml_node<> const* nodeP, int depth = 0)
{
    static int callNo = 0;
    callNo += 1;
    if(nodeP)
    {
        std::cout << std::setw(depth*2) << "" << nodeP->name()/* << " (" << nodeP->value() << ") (call " << callNo << ", depth " << depth << ")" */ << "\n";
        for (xml_node<>* child = nodeP->first_node(); child; child = child->next_sibling())
        {
            auto name = child->name();
            if(name && name[0])
            {
                xmlTreePresent(child, depth + 1);
            }
        }
    } else
    {
        std::cout << std::setw(depth*2) << "" << "NULL NODE\n";
    }
}

int main(int argc, char* argv[])
{
    std::ifstream ifs(argc>1? argv[1] : "input.txt");
    std::string xml(std::istreambuf_iterator<char>(ifs), {});

    try
    {
        xml_document<> doc;
        doc.parse<0>(&xml[0]);
        xmlTreePresent(doc.first_node());

        return 0;
    }
    catch(parse_error& e) { printf("PARSE ERROR: %s\n", e.what()); }
    catch(...)            { printf("GENERIC ERROR during doc.parse\n"); }
    return 1;
}
