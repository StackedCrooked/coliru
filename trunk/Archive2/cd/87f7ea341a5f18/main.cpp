#include <iostream>
#include <regex>
#include <string>

int main()
{
    std::string s("aaabbbccd123456eeffgg");
    std::regex pattern(R"((\D+)(\d+)(\D+))");

    std::smatch match;
    std::regex_match(s, match, pattern);
    std::cout << "Number of matches: " << match.size() << '\n';  
    for (auto const & sm : match) { std::cout <<  sm.str() << '\n'; }
}