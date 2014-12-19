#include <iostream>
#include <complex>
 
int main()
{
    using namespace std::literals::complex_literals;
    std::complex<double> c = 1.0 + 1i;
    std::cout << "abs" << c << " = " << abs(c) << '\n';
}