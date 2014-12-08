#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <sstream>
#include <type_traits>
#include <boost/lexical_cast.hpp>

int main()
{
    std::vector<std::string> vec{"a", "b", "c"};
    
    for (auto& str : vec)
    {
        std::cout << str << std::endl;
    }
}
