#include <cmath>
#include <complex>
#include <functional>
#include <iostream>
#include <valarray>

using cplx = std::complex<double>; // to save some typing

cplx f_of_ten(std::function<cplx(const cplx &)> x) // the problematic one
{
    return x(10);
}

cplx g_of_ten(cplx(*x)(const cplx &)) // this works
{
    return (*x)(10);
}


int main()
{
    std::cout << f_of_ten(std::sqrt<double>) << std::endl; // compile ERROR here!!!
    std::cout << g_of_ten(std::sqrt) << std::endl;
}
