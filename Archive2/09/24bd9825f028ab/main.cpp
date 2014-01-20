#include <iostream>


constexpr uint factorial(uint n) {
    return (n > 1) ? n * factorial(n-1) : 1;
}

int main() {
    std::cout << factorial(5) << std::endl;
}