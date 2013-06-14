#include <iostream>
#include <string>
#include <vector>

std::ostream& operator<<(std::ostream& os, const std::vector<std::string> & words) {
    for (const auto & word : words) {
        os << word << " ";
    }
    return os;
}

int main() {
    std::vector<std::string> words = { "Hello", "from", "GCC", __VERSION__, "!" };    
    std::cout << words << std::endl;
}