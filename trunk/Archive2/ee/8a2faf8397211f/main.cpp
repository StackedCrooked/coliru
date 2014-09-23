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

template<class T>
std::string convert_to_string(T t, int precision = 0)
{
    comma_facet cf{1}; // set ref count to 1 to prevent deleting
    std::ostringstream oss;
    oss.imbue(std::locale(std::cout.getloc(), &cf));
    oss << std::fixed << std::setprecision(precision) << t;
    return oss.str();
}

int main()
{
    auto d = 12345678.99;

    std::cout << std::fixed << std::setprecision(10) << "double: default locale: " << d << '\n';
    std::cout << "double: locale with modified numpunct: " << convert_to_string(d, 10) << '\n';

    auto i = 1234567890987654321L;

    std::cout << "int: default locale: " << i << '\n';
    std::cout << "int: locale with modified numpunct: " << convert_to_string(i) << '\n';

    std::cout << "double(int): default locale: " << (double)i << '\n';
    std::cout << "double(int): locale with modified numpunct: " << convert_to_string((double)i) << '\n';
}
