#include <iostream>
#include <regex>
#include <set>
#include <string>

struct S {
    const uint8_t top;
    const uint8_t bottom;
    const std::string name;
};

int main() {
    std::string text = "Top=0;Bottom=6;Name=Foo;";

    std::regex r{R"([^;]+;)"};
    std::set<std::string> tokens{std::sregex_token_iterator{std::begin(text), std::end(text), r}, std::sregex_token_iterator{}};

    auto it = std::begin(tokens);
    uint8_t bottom = std::stoul(it->substr(0, it->size() - 1).substr(it->find("=") + 1));
    ++it;
    std::string name = it->substr(0, it->size() - 1).substr(it->find("=") + 1);
    ++it;
    uint8_t top = std::stoul(it->substr(0, it->size() - 1).substr(it->find("=") + 1));

    S s{top, bottom, name};

    std::cout << "Top: " << static_cast<unsigned>(s.top) << std::endl;
    std::cout << "Bottom: " << static_cast<unsigned>(s.bottom) << std::endl;
    std::cout << "Name: " << s.name << std::endl;
}