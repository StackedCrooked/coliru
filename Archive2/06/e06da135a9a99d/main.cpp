#include <string>
#include <regex>
#include <iostream>

int main() {
    std::regex pat(R"(^(?:PING)\s(.+))");
    std::string s = "PING :some.server.net";
    if (std::regex_match(s, pat))  {
        std::cout << "matched" << std::endl;
    }
}