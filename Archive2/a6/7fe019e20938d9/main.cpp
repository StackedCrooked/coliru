#include <iostream>
#include <locale>
#include <iomanip>
#include <sstream>
 
struct comma_facet : std::numpunct<char> 
{
    using std::numpunct<char>::numpunct;
    char do_thousands_sep()   const { return ','; }  // separate with commas
    std::string do_grouping() const { return "\3"; } // groups of 3 digits
};

 
std::string convert_to_string(double d, int precision)
{
    comma_facet cf{1}; // set ref count to 1 to prevent deleting
    std::ostringstream oss;
    oss.imbue(std::locale(std::cout.getloc(), &cf));
    oss << std::fixed << std::setprecision(precision) << d;
    return oss.str();
}

int main()
{
    auto d = 12345678.99;

    std::cout << std::fixed << std::setprecision(10) << "default locale: " << d << '\n';
    std::cout << "locale with modified numpunct: " << convert_to_string(d, 10) << '\n';
}
