#include <iomanip>
#include <iostream>

int main() {
    float f = 1.10f;
    std::cout << std::setprecision(3) << f << std::endl;
    // Prints 0.91 isntead of 1.10
}