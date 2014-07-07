#include <iostream>
#include <string>
#include <regex>
#include <iomanip>
 
int main()
{
    std::regex regex("\\d+:\\d+");
    std::smatch result;
    std::cout << 
        std::boolalpha << std::regex_match(std::string("1:2"), result, regex) << 
        std::endl;
}