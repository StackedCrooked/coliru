#include <string>
#include <iostream>

int main() {
    std::string one = "HIA";
    std::string two = one;
    std::cout << (void*)one.c_str() << ' ' << (void*)two.c_str();
}