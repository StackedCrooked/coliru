#include <iomanip>
#include  <cmath>

#include <iostream>
int main(int argc, char** argv) {
    std::cout << std::setprecision(500) << std::nextafter(1./90, 0) << "\n";
    std::cout << std::setprecision(500) << (1./90) << "\n";
    std::cout << std::setprecision(500) << std::nextafter(1./90, 1) << "\n";
    return 0;
}