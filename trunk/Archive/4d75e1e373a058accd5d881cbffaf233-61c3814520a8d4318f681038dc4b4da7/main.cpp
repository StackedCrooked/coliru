#include <iostream>
int main() {
    float var = ~0u;
    if (var == var-1.0)
        std::cout << "SAME!";
    else
        std::cout << "DIFFERENT!";
}