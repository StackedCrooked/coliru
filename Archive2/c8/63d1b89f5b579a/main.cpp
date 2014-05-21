#include <iostream>
#include <regex>

int main() {
    std::regex re(R"(abc\+xyz)");
    std::cout << std::boolalpha << std::regex_match("abc+xyz", re) << std::endl;
}