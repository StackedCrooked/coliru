#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>
#include <regex>

int main()
{
    std::string manufacturer{"This is a test stri;ng with special chars"};
    
    // This will return TRUE (match) also for empty strings.
    static std::regex const regex{R"([\w\s]*)"};
    if (std::regex_match(manufacturer, regex))
    {
        std::cout << "Match found\n";
    }
    else
    {
        std::cout << "Match not found\n";
    }
}
