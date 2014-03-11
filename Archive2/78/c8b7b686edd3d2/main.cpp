#include <iostream>
#include <sstream>
#include <string>

#include <functional> // functional
using namespace std::placeholders;
 
#include <boost/math/tools/minima.hpp>
 
double f(double x, int y, int z) 
{ return (y*sin(x) + z + x * cos(x)); }
 
int main(int argc, char** argv)
{
    typedef std::pair<double, double> Result;
    // find a root of the function f in the interval x=[3.0, 4.0] with 20-bit precision
    Result r2 = boost::math::tools::brent_find_minima(std::bind(f, _1, 3, 4), 3.0, 4.0, 20);
    std::cout << "x=" << r2.first << " f=" << r2.second << std::endl;
    return 0;
}
 
// output:
// x=3.93516 f=-0.898333
