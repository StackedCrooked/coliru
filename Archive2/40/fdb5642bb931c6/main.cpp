#include <iostream>
#include <cmath>
#include <array>

#ifndef pow2C
double __tmpDouble__;
#define pow2C(a) ((__tmpDouble__=(a))*(__tmpDouble__))
#endif


inline double calculateDistance(double *x, double *y, int NDims) 
{
    double d = 0;
    for (int i = 0; i < NDims; i++)
    // it is faster to calculate the difference once
       d += pow2C(x[i] - y[i]);
    return sqrt(d);
}

int main()
{
    const size_t NUM_DIMS = 3;
    std::array<double, NUM_DIMS> x{{5.0, 6.0, 7.0}};
    std::array<double, NUM_DIMS> y{{1.2, 1.5, 9.0}};
    
    std::cout << "Distance between x and y is: " << calculateDistance(&x[0], &y[0], NUM_DIMS) << '\n';
}