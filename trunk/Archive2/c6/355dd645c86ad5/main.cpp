#include <regex>
#include <iostream>
#include <string>

std::string get() {
    return std::string("foo bar");
}

int main() {
    std::smatch matches;
    std::regex_match(get(), matches, std::regex("^(foo).*"));
    std::cout << matches[1] << std::endl;
}