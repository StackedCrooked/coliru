#include <iostream>
#include <string>

template <typename T>
int P(T num) {
    return num == std::string::npos ? -1 : num;
}


int main() {
    std::string text("abcdef");
    
    
    std::cout << P(text.find("", 0)) << " " << P(text.find_first_of("", 0)) << std::endl;
    std::cout << P(text.find("", 1)) << " " << P(text.find_first_of("", 1)) << std::endl;
    std::cout << P(text.find("", -1)) << " " << P(text.find_first_of("", -1)) << std::endl;
    
    text.clear();
    
    std::cout << P(text.find("", 0)) << " " << P(text.find_first_of("", 0)) << std::endl;
    std::cout << P(text.find("", 1)) << " " << P(text.find_first_of("", 1)) << std::endl;
    std::cout << P(text.find("", -1)) << " " << P(text.find_first_of("", -1)) << std::endl;
    
    std::cout << P(text.find("a", 0)) << " " << P(text.find_first_of("a", -1)) << std::endl;
}