#include <algorithm>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

struct S {
    const uint8_t top;
    const uint8_t bottom;
    const std::string name;
};

int main() {
    std::string text = "Top=0;Bottom=6;Name=Foo;";

    std::regex r{R"([^;]+;)"};
    std::vector<std::string> tokens{std::sregex_token_iterator{std::begin(text), std::end(text), r}, std::sregex_token_iterator{}};

    std::sort(std::begin(tokens), std::end(tokens));
    for (auto&& t : tokens) {
        t = t.substr(0, t.size() - 1).substr(t.find("=") + 1);
    }

    S s{static_cast<uint8_t>(std::stoul(tokens[2])), static_cast<uint8_t>(std::stoul(tokens[0])), tokens[1]};

    std::cout << "Top: " << static_cast<unsigned>(s.top) << std::endl;
    std::cout << "Bottom: " << static_cast<unsigned>(s.bottom) << std::endl;
    std::cout << "Name: " << s.name << std::endl;
}