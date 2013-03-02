#include <regex>
#include <sstream>
#include <vector>
#include <iostream>

int main() {
    std::string str = R"d(Would "you" like to have responses to your "questions" sent to you via email?)d";
    std::regex rgx(R"(\"(\w+)\")");
    std::smatch match;
    std::string buffer;
    std::stringstream ss(str);
    std::vector<std::string> strings;
    //Split by whitespaces..
    while(ss >> buffer) 
        strings.push_back(buffer);
    for(auto& i : strings) {
        if(std::regex_match(i,match, rgx)) {
            std::ssub_match submatch = match[1];
            std::cout << submatch.str() << '\n';
        }
    }
}