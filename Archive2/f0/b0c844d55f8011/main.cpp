#include <iostream>
#include <array>
#include <string>

int main() {
    std::array<std::string, 3> m = {"123", "456", "789"};
    for (auto& s : m) 
        std::cout << s;
}