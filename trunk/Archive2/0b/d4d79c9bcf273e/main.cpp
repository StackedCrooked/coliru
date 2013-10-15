#include <cmath>
#include <cfloat>
#include <limits>
#include <iostream>
using std::cout;

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
  if(d1 != d2)
    cout << "d1 != d2: " << d << '\n';
  if(d1 != d3)
    cout << "d1 != d3: " << d << '\n';
  if(d2 != d3)
    cout << "d2 != d3: " << d << '\n';
}

int main()
{
  test(0.1);
  test(986546357654.354687);
}