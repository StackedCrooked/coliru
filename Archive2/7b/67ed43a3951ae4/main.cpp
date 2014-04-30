#include <boost/range/adaptors.hpp>

using namespace boost::adaptors;
#include <iostream>

int main()
{
    std::map<int, std::string> const map_obj {
        { 0x0001, "one"   },
        { 0x0002, "two"   },
        { 0x0003, "three" },
        { 0x0404, "four"  },
        { 0x0005, "five"  },
    }; 

    const int match_value = 0xFF00;
    for(auto& v : map_obj
         | filtered([=](std::pair<const int, std::string> const& p) { return (p.first & match_value) != 0; })
         | map_values)
    {
        std::cout << v << "\n";
    }
}
