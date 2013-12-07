#include <iostream>
#include <string>
#include <vector>

int main() {
    std::cout << "A:";
    const std::vector<std::string> a{"a", "b"};
    for(auto&& i : a) std::cout << i << ' ';
    
    std::cout << "\nB:";
    const std::vector<std::string> b{{"a", "b"}};
    for(auto&& i : b) std::cout << i << ' ';
    
    std::cout << "\nC:";
    const std::vector<std::string> c = {"a", "b"};
    for(auto&& i : c) std::cout << i << ' ';
    
}
