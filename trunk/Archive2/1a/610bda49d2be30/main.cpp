#include <iostream>
#include <string>

template <typename T>
int P(T num) {
    return num == std::string::npos ? -1 : num;
}


int main() {
    std::string text("abcdef");
    
    std::cout << P(text.rfind("", -1)) << " " << P(text.find_last_of("", -1)) << std::endl;
    std::cout << P(text.rfind("", 1)) << " " << P(text.find_last_of("", 1)) << std::endl;
    std::cout << P(text.rfind("", 0)) << " " << P(text.find_last_of("", 0)) << std::endl;
    
    text.clear();
    
    std::cout << P(text.rfind("", -1)) << " " << P(text.find_last_of("", -1)) << std::endl;
    std::cout << P(text.rfind("", 1)) << " " << P(text.find_last_of("", 1)) << std::endl;
    std::cout << P(text.rfind("", 0)) << " " << P(text.find_last_of("", 0)) << std::endl;
    
    std::cout << P(text.rfind("a")) << " " << P(text.find_last_of("a")) << std::endl;
}