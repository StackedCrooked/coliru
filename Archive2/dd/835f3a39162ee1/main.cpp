#include <iostream>
#include <iomanip>

int main() {
    double v = 10.0/3.;
    std::cout << std::setw(10) << v << ".\n";
    std::cout << std::setw(5) << std::setprecision(2) << std::fixed << v << ".\n";
    std::cout << std::setw(5) << std::setprecision(2) << v << ".\n";
    std::cout << std::setw(5) << std::setprecision(2) << v << ".\n";
}