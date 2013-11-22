#include <cmath>
#include <utility>
#include <iostream>
 
std::pair<double, double> cartesian_to_polar(double x, double y)
{
    return {std::hypot(x, y), std::atan2(y,x)};
}
 
int main()
{
    std::pair<double, double> polar = cartesian_to_polar(1, 1);
    std::cout << "(1,1) cartesian is (" << polar.first
               << "," << polar.second<< ") polar\n";
}