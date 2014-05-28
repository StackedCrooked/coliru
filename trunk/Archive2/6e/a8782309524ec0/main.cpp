#include <iostream>
#include <string>
#include <algorithm>

int main() {
    std::cout << "What's your name? ";
    std::string name;
    std::getline(std::cin, name);
    std::reverse(name.begin(), name.end());
    std::cout << "YOUR NAME REVERSED IS \"" << name << "\"\n";
}