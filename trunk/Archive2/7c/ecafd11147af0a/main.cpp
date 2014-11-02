#include<iostream>
#include<string>
#include<regex>

int main()
{
    std::string input{ "Mon Nov 25 20:54:36 2013" };
    //Day:: Exactly Two Number surrounded by spaces in both side
    std::regex  r{R"(.*?\s(\d{2})\s.*)"};
    std::smatch match;

    if (std::regex_match(input,match,r)) {
        std::cout << "Found" << "\n";
        if (match.ready()){
            std::string out = match[1];
            std::cout << out << "\n";
        }
    } else {
        std::cout << "Did Not Found" << "\n";
    }

    if (std::regex_search(input, match,r)) {
        std::cout << "Found" << "\n";
        if (match.ready()){
            std::string out = match[1];
            std::cout << out << "\n";
        }
    }
    else {
        std::cout << "Did Not Found" << "\n";
    }
}
