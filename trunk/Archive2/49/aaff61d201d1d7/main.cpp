#include <iostream>
#include <iomanip>
#include <cmath>

double specialRound(double x, int precision) {
    return std::round((static_cast<long long>(x * std::pow(10.0, precision + 1)) - 1) / 10.0 + 0.05) / std::pow(10.0, precision);
}

int main() {
    std::cout << std::setprecision(10);
    std::cout << specialRound(123.4561235999, 6) << std::endl;
    std::cout << specialRound(123.4561236000, 6) << std::endl;
}