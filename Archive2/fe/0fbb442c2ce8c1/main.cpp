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

boost::property_tree::ptree ptree_to_utree(boost::property_tree::ptree org)
{
    boost::property_tree::ptree dup;
    dup.put_value(org.get_value(""));
    if(org.size() == 0)
    {
        return dup;
    }
    else
    {
        for (const auto& kv : org) 
        {   
            dup.put_child(kv.first,ptree_to_utree(kv.second));
        }
        return dup;
    }
}

int main()
{
    
     std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
    
    boost::property_tree::ptree fptree;
    read_xml("test.xml",fptree,4);
    
    boost::property_tree::ptree dup;
    
    dup = ptree_to_utree(fptree);
    
    for (const auto& kv : dup) 
        {  
            std::cout<< kv.first << " - ";
            for (const auto& kv2 : kv.second)
            {
                std::cout<< kv2.first << " - ";
            }
        }
    
    std::cout<<"\n";
    
    for (const auto& kv : fptree) 
        {  
            std::cout<< kv.first << " - ";
            for (const auto& kv2 : kv.second)
            {
                std::cout<< kv2.first << " - ";
            }
        }
    
    
}
