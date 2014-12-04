#include <iostream>
#include <string>


int main() {
    std::string text("abcdef");
    
    std::cout << text.find("", 0) << std::endl;
    std::cout << text.find("", 1) << std::endl;
    std::cout << text.find("", -1) << std::endl;
    
    text.clear();
    
    std::cout << text.find("", 0) << std::endl;
    std::cout << text.find("", 1) << std::endl;
    std::cout << text.find("", -1) << std::endl;
    
    std::cout << text.find("a", 0) << std::endl;
}