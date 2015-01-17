#include <iostream>
#include <complex>
#include <cstdint>
#include <cstring>

int main()
{
     std::complex<double> c(-61.887073591767951,-60.052083270252012);
    double a = (1.0 / c).real();
//    std::cout << std::setprecision(17) << " " << a << std::endl;
    uint64_t i;
    memcpy(&i, &a, 8);
    std::cout << std::hex << i << std::endl;
    return 0;
}