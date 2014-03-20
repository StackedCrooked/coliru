#include <iostream>
#include <sstream>
#include <stdexcept>

double safe_float_conversion(const std::string& s)
{
    std::stringstream ss;
    double d;
    ss << s;

    if(ss >> d) {
        return d;
    }
    throw std::invalid_argument("not a number");
}

int main()
{
    double x = safe_float_conversion("3.45");
    double y = safe_float_conversion("abcd");
    std::cout << x << "\n";
    std::cout << y << "\n";
}
    