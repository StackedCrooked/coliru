#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cmath>
#include <limits>


using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

inline const unsigned long long& ToInt(const double& value)
{
    return *reinterpret_cast<const unsigned long long*>(&value);
}

inline const double& ToDouble(const unsigned long long& value)
{
    return *reinterpret_cast<const double*>(&value);
}


int main()
{
    
    const long double pi = std::acos(-1.L);
    std::cout << "default precision (6): " << pi << '\n'
              << "std::precision(10):    " << std::setprecision(10) << pi << '\n'
              << "max precision:         "
              << std::setprecision(std::numeric_limits<long double>::digits10 + 1)
              << pi << '\n';
              
              
    double a = 100, b = 10; 
    
    auto truc = ToDouble( ToInt(a) | ToInt(b) );
    
    cout << "a: " << a << "\n"
    << "b: " << b << "\n"
    << "truc: " << truc << "\n"
    << endl;
    
    
    
}
