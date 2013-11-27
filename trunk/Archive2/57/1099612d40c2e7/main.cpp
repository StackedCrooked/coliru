#include <iostream>
#include <vector>
#include <array>


int main() {
    std::array<std::string, 3> texts = {"Apple", "Banana", "Orange"};
    
    for(const auto& text : texts) {
        std::cout << text << std::endl;
    }
}