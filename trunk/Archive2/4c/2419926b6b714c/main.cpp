#include <iostream>
#include <regex>
#include <string>

int main() {
    std::regex pattern{ "[A-Z]:(\\d*)" };
    std::string cible{ "A:4732" };
    std::smatch sm;
    std::regex_match(cible,sm,pattern);
    for(unsigned int i{0}; i < sm.size(); i++)
        std::cout << sm[i] << std::endl;
}