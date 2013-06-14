#include <iostream>
#include <string>
#include <vector>

using Words = std::vector<std::string>;

std::ostream& operator<<(std::ostream& os, const Words & words) {
    for (const auto & word : words) {
        os << word << " ";
    }
    return os;
}

int main() {
    Words words = { "Hello", "from", "GCC", __VERSION__, "!" };    
    std::cout << words << std::endl;
}