#include <regex>
#include <iostream>

int main() {
    std::string s = "this is a test string";
    s = std::regex_replace(s, std::regex("\\s"), "\\s*");

    std::cout << s;
}