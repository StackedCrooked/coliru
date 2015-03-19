#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cmath>
#include <limits>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

inline unsigned long long& ToInt(double& value)
{
    return *reinterpret_cast<unsigned long long*>(&value);
}

inline double& ToDouble(unsigned long long& value)
{
    return *reinterpret_cast<double*>(&value);
}


int main()
{
    
    const long double pi = std::acos(-1.L);
    std::cout << "default precision (6): " << pi << '\n'
              << "std::precision(10):    " << std::setprecision(10) << pi << '\n'
              << "max precision:         "
              << std::setprecision(std::numeric_limits<long double>::digits10 + 1)
              << pi << '\n';
              
              
             double a, b; 
    auto truc = ToDouble( ToInt(a) | ToInt(b) );
}
