#include <iostream>
#include <string>
#include <vector>


int main() {
    const char* str = R"(\nHello world!)""\nHello world)";
                        
    std::cout << str;
    
}