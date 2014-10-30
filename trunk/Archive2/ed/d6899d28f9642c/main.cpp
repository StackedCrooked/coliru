#include <cmath>
#include <iostream>

int main()
{
   const double x = 1.25;
   
   double whole = 0;
   double frac  = modf(x, &whole);
   
   std::cout << whole << '/' << (1/frac) << '\n';
}