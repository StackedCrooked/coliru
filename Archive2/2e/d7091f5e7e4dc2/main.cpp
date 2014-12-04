#include <iostream>
#include <string>


int main() {
    std::string text("abcdef");
    
    std::cout << text.rfind("", -1) << std::endl;
    std::cout << text.rfind("", 1) << std::endl;
    std::cout << text.rfind("", 0) << std::endl;
    
    text.clear();
    
    std::cout << text.rfind("", -1) << std::endl;
    std::cout << text.rfind("", 1) << std::endl;
    std::cout << text.rfind("", 0) << std::endl;    
}