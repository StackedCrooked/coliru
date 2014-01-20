#include <ios>
#include <iomanip>
#include <iostream>
#include <sstream>
 
int main() 
{
    double OverallVolume = 1535625179.1619387;
    std::ostringstream ss;
    
    ss << std::scientific << std::setprecision(7) << OverallVolume;
    std::cout << ss.str() << '\n';
}
