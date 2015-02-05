#include <string>
#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <memory>
#include <sstream>

template<typename T1, typename T2>
T1 lexical_cast(T2 const& value, T1 const& defaultValue = T1{})
{
    T1 convertedValue;
    std::stringstream ss;
    if (!(ss << value) || !(ss >> convertedValue))
    {
        return defaultValue;
    }
  
    return convertedValue;
}
   
int main()
{
    int test1 = lexical_cast<int>("100");
    std::string test2 = lexical_cast<std::string>(100);
    int test3 = lexical_cast<int>("abc");
    int test4 = lexical_cast<int>("abc", -1);
    
    std::cout
        << "Test1: " << test1 << std::endl
        << "Test2: " << test2 << std::endl
        << "Test3: " << test3 << std::endl
        << "Test4: " << test4 << std::endl
        ;
}