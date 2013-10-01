#include <cmath>
#include <cfenv>
#include <iostream>
 
int main()
{
    #pragma STDC FENV_ACCESS ON
    std::fesetround(FE_DOWNWARD);
    std::cout << "rounding using FE_DOWNWARD: \n" << std::fixed
              << " 12.0 ->  " << std::nearbyint(12.0) << '\n'
              << " 12.1 ->  " << std::nearbyint(12.1) << '\n'
              << "-12.1 -> " << std::nearbyint(-12.1) << '\n'
              << " 12.5 ->  " << std::nearbyint(12.5) << '\n'
              << " 12.9 ->  " << std::nearbyint(12.9) << '\n'
              << "-12.9 -> " << std::nearbyint(-12.9) << '\n'
              << " 13.0 ->  " << std::nearbyint(13.0) << '\n';
    std::fesetround(FE_TONEAREST);
    std::cout << "rounding using FE_TONEAREST: \n"
              << " 12.0 ->  " << std::nearbyint(12.0) << '\n'
              << " 12.1 ->  " << std::nearbyint(12.1) << '\n'
              << "-12.1 -> " << std::nearbyint(-12.1) << '\n'
              << " 12.5 ->  " << std::nearbyint(12.5) << '\n'
              << " 12.9 ->  " << std::nearbyint(12.9) << '\n'
              << "-12.9 -> " << std::nearbyint(-12.9) << '\n'
              << " 13.0 ->  " << std::nearbyint(13.0) << '\n';
}