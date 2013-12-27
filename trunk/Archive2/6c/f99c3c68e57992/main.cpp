#include <iostream>
#include <string>
#include <regex>
 
int main()
{
    std::string lines[] = {"Roses are #ff0000",
                           "violets are #0000ff",
                           "all of my base are belong to you"};
 
    std::regex color_regex("#([a-f0-9]{2})"
                            "([a-f0-9]{2})"
                            "([a-f0-9]{2})");
 
    for (const auto &line : lines) {
        std::cout << line << ": " 
                  << std::regex_search(line, color_regex) << '\n';
    }   
 
    std::smatch color_match;
    for (const auto &line : lines) {
        std::regex_search(line, color_match, color_regex);
        std::cout << "matches for '" << line << "'\n";
        for (size_t i = 0; i < color_match.size(); ++i) {
            std::ssub_match sub_match = color_match[i];
            std::string sub_match_str = sub_match.str();
            std::cout << i << ": " << sub_match_str << '\n';
        }   
    }   
}