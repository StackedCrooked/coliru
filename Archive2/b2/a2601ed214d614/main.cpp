#include <iostream>

int main()
{
    double a = 1.2345;
    
    std::string s(16, '\0');
    auto written = std::snprintf(&s[0], s.size(), "%.2f", a);
    s.resize(written);
    
    std::cout << s;
}