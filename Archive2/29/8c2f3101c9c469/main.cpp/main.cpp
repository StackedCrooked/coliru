#include <iostream>
#include <string>

constexpr unsigned int str2int(const char* str, int h = 0) {
    return !str[h] ? 5381 : (str2int(str, h+1)*33) ^ str[h];
}

int main() {
    const std::string n = "Floris";
    
    switch(str2int(n.c_str())) {
    case str2int("Floris"):
        std::cout << "Oh hai" << std::endl;
        break;
    default:
        break;
    }
}