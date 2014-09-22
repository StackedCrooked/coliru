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
    
    comma_facet cf{1};

    std::cout << std::fixed << std::setprecision(10) << "default locale: " << d << '\n';
    auto old_locale = std::cout.imbue(std::locale(std::cout.getloc(), &cf));
    std::cout << std::fixed << std::setprecision(10) << "locale with modified numpunct: " << d << '\n';
    std::cout.imbue(old_locale);
    std::cout << std::fixed << std::setprecision(10) << "back to default locale: " << d << '\n';
}
