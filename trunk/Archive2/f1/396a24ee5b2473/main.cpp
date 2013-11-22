#include <iostream>
#include <regex>

int main() {
    std::string string("string");
    if(regex_match(string, std::regex{"string", std::regex::icase}))
        std::cout << "Match!\n";
}