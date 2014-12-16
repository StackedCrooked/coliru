#include <string>
#include <iostream>
#include <regex>
#include <sstream>

namespace ttm {
    
    template<class T>
    T lexical_cast(std::string const& value, T const& default_value = T{})
    {
       T converted_value;
       std::istringstream ss{value};
       if (!(ss >> converted_value))
       {
          return default_value;
       }
    
       return converted_value;
    }
}

int main()
{
    std::cout << "Good: " << ttm::lexical_cast<int>("123", 100) << std::endl;
    std::cout << "Bad: " << ttm::lexical_cast<int>("abc", 100) << std::endl;
}