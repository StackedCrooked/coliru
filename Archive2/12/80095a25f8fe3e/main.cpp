#include <iostream>
#include <utility>

int main() {
    int x{5};
    std::cout << "Initial value of x: " << x << '\n';
    
    int result = std::exchange(x, 9);
    
    std::cout << "Result of exchange(): " << result << '\n';
    std::cout << "New value of x: " << x << '\n';
}