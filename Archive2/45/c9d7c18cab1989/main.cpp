#include <iostream>
#include <regex>
#include <string>

int main() 
{
    std::regex r{"Word[[:digit:]]Word"};
    
    if(std::regex_match("Word4Word", r)) {
        std::cout << "match\n";
    } else {
        std::cout << "no match\n";
    }
}
