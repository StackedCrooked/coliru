#include <iostream>

int main(...)
{
    int tunref = 1000;
    int n = 13;
    int r = 15;
    int ppbOffset = 35;
    double f = ((double)tunref * n / r) * (1.0 + 1e-9 * ppbOffset);
    std::cout << "f=" << f << std::endl;
    std::cout << "(double)tunref * n / r = " << ((double)tunref * n / r) << std::endl;
    std::cout << "(double)tunref * (double)n / r = " << ((double)tunref * (double)n / r) << std::endl;
    std::cout << "(double)tunref * n / (double)r = " << ((double)tunref * n / (double)r) << std::endl;
    std::cout << "(double)tunref * (double)n / (double)r = " << ((double)tunref * (double)n / (double)r) << std::endl;
}