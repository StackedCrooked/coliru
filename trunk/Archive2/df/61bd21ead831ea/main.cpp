#include <iostream>
#include <sstream>
#include <locale>
#include <iomanip>
int main()
{
    std::istringstream in("$1,234.56 2.22 USD  3.33");
    long double v1, v2;
    std::string v3;
    in.imbue(std::locale("en_US.UTF-8"));
    in >> std::get_money(v1) >> std::get_money(v2) >> std::get_money(v3, true);
 
    std::cout << '"' << in.str() << "\" parsed as: "
              << v1 << ", " << v2 << ", " << v3 << '\n';
}