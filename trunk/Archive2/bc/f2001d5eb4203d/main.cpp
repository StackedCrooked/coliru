#include <iostream>
#include <string>
#include <regex>

int main()
{
    std::string input{ "Mon Nov 25 20:54:36 2013" };
    
    std::regex  r{R"(^(\w{3}) (\w{3}) (\d{2}) (\d{2}):(\d{2}):(\d{2}) (\d{4})$)"};
    std::smatch match;

    if (std::regex_match(input,match,r)) {
        std::cout << "Found" << "\n";
        if (match.ready()){
            for(auto const& m : match) {
                std::cout << m << '\n';
            }
        }
    } else {
        std::cout << "Did Not Found" << "\n";
    }
}
