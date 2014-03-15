#include <iostream>
#include <cmath>
#include <iomanip>
double phi(double x1, double x2)
{
    return (std::erf(x2/std::sqrt(2)) - std::erf(x1/std::sqrt(2)))/2;
}
int main()
{
    std::cout << "normal variate probabilities:\n";
    for(int n=-4; n<4; ++n)
        std::cout << "[" << std::setw(2) << n << ":" << std::setw(2) << n+1 << "]: "
                  << std::setw(5) << std::fixed << std::setprecision(2)
                  << 100*phi(n, n+1) << "%\n";
}