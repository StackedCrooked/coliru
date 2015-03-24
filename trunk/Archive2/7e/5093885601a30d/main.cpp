#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cmath>
#include <limits>
#include <sstream>
#include <regex>


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
    
    std::string text = "1.234e-00050";
    std::regex match("e-?0+");
    std::cout << '\n' << std::regex_replace(text, match, "e-") << '\n';    
    
}
