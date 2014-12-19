#include <iostream>
#include <cmath>
#include <cfenv>
 
#pragma STDC FENV_ACCESS ON
const double pi = std::acos(-1);
double cos_pi_x_naive(double x) { return std::cos(pi * x); }
// the period is 2, values are (0;0.5) positive, (0.5;1.5) negative, (1.5,2) positive
double cos_pi_x_smart(double x)
{
    int quadrant;
    double rem = std::remquo(x, 1, &quadrant);
    quadrant = (unsigned)quadrant % 4; // keep 2 bits to determine quadrant
    switch(quadrant) {
        case 0: return std::cos(pi * rem);
        case 1: return -std::cos(pi * rem);
        case 2: return -std::cos(pi * rem);
        case 3: return std::cos(pi * rem);
    };
}
int main()
{
    std::cout << "cos(pi * 0.25) = " << cos_pi_x_naive(0.25) << '\n'
              << "cos(pi * 1.25) = " << cos_pi_x_naive(1.25) << '\n'
              << "cos(pi * 1000000000000.25) = "
              << cos_pi_x_naive(1000000000000.25) << '\n'
              << "cos(pi * 1000000000001.25) = "
              << cos_pi_x_naive(1000000000001.25) << '\n'
              << "cos(pi * 1000000000000.25) = "
              << cos_pi_x_smart(1000000000000.25) << '\n'
              << "cos(pi * 1000000000001.25) = "
              << cos_pi_x_smart(1000000000001.25) << '\n';
    // error handling
    std::feclearexcept(FE_ALL_EXCEPT);
    int quo;
    std::cout << "remquo(+Inf, 1) = " << std::remquo(INFINITY, 1, &quo) << '\n';
    if(fetestexcept(FE_INVALID)) std::cout << "    FE_INVALID raised\n";
}