#include <complex>
#include <iostream>
 
int main()
{
   const double pi = std::acos(-1);
   const std::complex<double> i(0, 1);
 
   std::cout << std::fixed << " exp(i*pi) = " << std::exp(i * pi) << '\n';
}