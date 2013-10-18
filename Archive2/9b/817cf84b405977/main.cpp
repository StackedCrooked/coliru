#include <iostream>
#include <string>
#include <regex>

int main()
{
    std::regex r("([ghn])");
    std::cout << std::regex_search("ghn", r) << std::endl;
}