#include <iostream>
#include <iomanip>

int main() {
    double d = 0.00000095;
    double e = 0.5;
    std::cout << std::setprecision(3);
    std::cout.unsetf(std::ios::floatfield);
    std::cout << "d = " << (100. * d) << "%\n";
    std::cout << "e = " << (100. * e) << "%\n";
    std::cout << std::fixed;
    std::cout << "d = " << (100. * d) << "%\n";
    std::cout << "e = " << (100. * e) << "%\n";
    std::cout << std::scientific;
    std::cout << "d = " << (100. * d) << "%\n";
    std::cout << "e = " << (100. * e) << "%\n";
}
