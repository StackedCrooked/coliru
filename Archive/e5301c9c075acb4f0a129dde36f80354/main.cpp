// Bisection method
// http://www.datasimfinancial.com/forum/viewtopic.php?t=111

#include <boost/math/tools/roots.hpp>
#include <cmath>
#include <iostream>

double func(double x)
{
   return exp(-x*x) - x*x*x + 2.0;
}

struct TerminationCondition  
{
  TerminationCondition(double tol) : tol_(tol) {}
  bool operator() (double min, double max)  
  {
    return abs(min - max) <= tol_;
  }
  double tol_;
};


int main()
{
  namespace Ed = boost::math::tools;
  boost::uintmax_t maxIter = 1000;

  double a  = -12.0;
  double b = 10.0;

  double tolerance = 0.000001;

  try // Needed because it checks f(a).f(b) < 0 or args in wrong order
  {
    auto res = Ed::bisect(&func, a, b, TerminationCondition(tolerance), maxIter);
    std::cout << "(" << res.first << ", " << res.second << ")\n";

    // Sanity check
    std::cout << func(res.first) << "," << func(res.second) << std::endl;

  }
  catch (const std::exception & ex)
  {
    std::cout << ex.what();
  }
}
