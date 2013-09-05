#include <iostream>


int main() {
    int x = 2;
    float f = 0.5f;
    
    auto u = f + x;
    decltype(x) uu = f + x;
    
    std::cout << "Auto: " << u << std::endl;
    std::cout << "Decltype: " << uu << std::endl;
}