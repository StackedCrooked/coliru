#include <math.h>
#include <fenv.h>
#include <iostream>
#include <iomanip>

int main()
{
    fesetround(FE_UPWARD);
    std::cout << std::setprecision(100)
              << float(atan(14.865f)) << '\n'
              << atanf(14.865f) << '\n';
}