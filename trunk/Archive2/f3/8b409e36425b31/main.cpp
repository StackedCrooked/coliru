#include <iostream>
#include <locale>
#include <iomanip>
 
struct comma_facet : std::numpunct<char> 
{
    char do_thousands_sep()   const { return ','; }  // separate with commas
    std::string do_grouping() const { return "\3"; } // groups of 3 digits
};

 
int main()
{
    auto d = 12345678.99;

    std::cout << std::fixed << std::setprecision(10) << "default locale: " << d << '\n';
    std::cout.imbue(std::locale(std::cout.getloc(), new comma_facet));
    std::cout << std::fixed << std::setprecision(10) << "locale with modified numpunct: " << d << '\n';
}
