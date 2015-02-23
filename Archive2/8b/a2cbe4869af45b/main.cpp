#include <iostream>
#include <string>
#include <regex>
 
int main()
{
    std::regex regex;
    std::smatch matches;
    
    std::string regex_str = "(\\d{1,2})\\/(\\d{1,2})\\/(\\d{2,4})";
    std::string date_str = "01/01/2002";
    
    std::cout << "regex: '" << regex_str << "'" << std::endl;

    regex = std::regex(regex_str.c_str());
    if (std::regex_match(date_str, matches, regex)) {
        std::cout << date_str << " is match" << std::endl;
        for(auto mstr : matches){
            std::cout << mstr << std::endl;
        }
    } else {
        std::cout << date_str << " not match" << std::endl;
        
    }
}