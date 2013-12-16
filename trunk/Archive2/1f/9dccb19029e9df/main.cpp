#include <iostream>

int main() {
    auto&& x = "text";
    std::cout << sizeof(x) << '\n';
    
    const char* y = "text";
    std::cout << sizeof(y) << '\n';
    
    const char z[] = "text";
    std::cout << sizeof(z) << '\n';
}