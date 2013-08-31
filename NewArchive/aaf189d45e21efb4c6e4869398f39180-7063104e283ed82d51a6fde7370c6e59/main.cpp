#include <iostream>
#include <string>
#include <vector>


int main() {
    const char* str = R"delim(\nHello world!)""\nHello world)delim";
                        
    std::cout << str;
    
}