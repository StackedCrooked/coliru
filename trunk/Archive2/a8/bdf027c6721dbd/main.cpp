#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <list>
#include <iostream>

using boost::property_tree::ptree;

struct structure
{
    std::string str;
    int ival;
    std::list<bool> bval;

    void save(const std::string& filename) {
        ptree pt;
        pt.put("main.str", str);
        pt.put("main.ival", ival);

        for (const auto& x : bval)
            pt.add("main.bval.b", x); 

        write_xml(filename, pt);
    }

    void load(const std::string& filename) {
        ptree pt;

        read_xml(filename, pt);

        str = pt.get("main.str", str);
        ival = pt.get("main.ival", ival);

        for(auto& v : pt.get_child("main.bval"))
        {
             bval.insert(bval.end(), "true" == v.second.data());
             std::cout << "bval is now " << bval.size() << " entries\n";
        }
    }
};

int main()
{
    structure b, s;
    s.str = "abc";
    s.ival = 14;
    s.bval = { 1, 0, 0, 1, 0, 1, 0, 0, 0, 1 };

    try
    {
        s.save("zxx.xml");

        b.load("zxx.xml");

        b.save("zxx2.xml");
    }
    catch (std::exception& exc)
    {
        std::cout << exc.what() << std::endl;
    }
    return 0;
}
