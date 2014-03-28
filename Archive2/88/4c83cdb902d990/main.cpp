#include <iostream>

int main() {
    std::cout << "Some output\n";
    
    auto buf = std::cout.rdbuf();
    std::cout.rdbuf(std::cerr.rdbuf());
    
    std::cout << "Some error\n";
    
    std::cout.rdbuf(buf);
    
    std::cout << "More output\n";
}