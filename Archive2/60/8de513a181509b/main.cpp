#include <cmath>
#include <cfloat>
#include <limits>
#include <iostream>
using std::cout;
#include <iomanip>
using std::setprecision;

#include <boost/math/special_functions/next.hpp>

double
epsFor( double x )
{
  union
  {
    double d;
    unsigned long long i;
  } tmp;
  tmp.d = x;
  ++ tmp.i;
  return tmp.d - x;
}

void test(double d)
{
  double d1 = std::nextafter(d,DBL_MAX);
  double d2 = d+std::numeric_limits<double>::epsilon() * d;
  double d3 = d+epsFor(d)*d;
  double d4 = boost::math::nextafter(d, DBL_MAX);
  cout << setprecision(40)
       << "For value of d = " << d << '\n'
       << " std::nextafter: " << d1 << '\n'
       << " Boost solution: " << d4 << '\n'
       << " numeric_limits: " << d2 << '\n'
       << " undefined beh.: " << d3 << '\n';
}

int main()
{
  test(0.1);
  test(986546357654.354687);
}