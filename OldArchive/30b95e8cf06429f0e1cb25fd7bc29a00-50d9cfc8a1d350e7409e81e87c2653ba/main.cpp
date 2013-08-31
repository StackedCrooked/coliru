#include <iostream>
#include <limits>

int main()
{
    float fInf = std::numeric_limits<float>::infinity();
    double dInf = std::numeric_limits<double>::infinity();
    std::cout << (fInf == fInf) << std::endl;
    std::cout << (dInf == dInf) << std::endl;
}
