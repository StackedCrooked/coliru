#include <iostream>
#include <string>
#include <vector>

int main() {
    std::vector<std::string> v{{"testing", "123"}};
    
    for (const auto &s : v) {
        std::cout << s << ' ';
    }
}