#include <cmath>
#include <cfloat>
#include <limits>
#include <iostream>
using std::cout;

void test(double d)
{
    double d1 = std::nextafter(d,DBL_MAX);
    double d2 = d+std::numeric_limits<double>::epsilon() * d;
    if(d1 != d2)
      cout << "uhoh: " << d << '\n';
}

int main()
{
  test(0.1);
  test(986546357654.354687);
}