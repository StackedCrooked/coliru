#include <iostream>
#include <string>
#include <vector>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

void print(boost::property_tree::ptree const& pt)
{
    using boost::property_tree::ptree;
    ptree::const_iterator end = pt.end();
    for (ptree::const_iterator it = pt.begin(); it != end; ++it) {
        std::cout << it->first << ": " << it->second.get_value<std::string>() << std::endl;
        print(it->second);
    }
}

boost::property_tree::ptree ptree_to_ptree(boost::property_tree::ptree org)
{
    boost::property_tree::ptree dup;
    dup.put_value(org.get_value(""));
    for (const auto& kv : org) 
    {   
        dup.add_child(kv.first,ptree_to_ptree(kv.second));
    }
    return dup;
}



int main()
{
    
     std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
    
    boost::property_tree::ptree org;
    read_xml("test.xml",org,4);
    
    boost::property_tree::ptree dup;
    
    dup = ptree_to_ptree(org);
   
    print(org);
    std::cout<<"\n";
    print(dup);
}
