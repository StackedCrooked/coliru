#include <iostream>
#include <locale>
 
int main()
{
    const double number = 1000.25;
    std::cout << "\"C\" locale: " << number << '\n';
    std::locale loc = std::locale().combine<std::numpunct<char>>(std::locale("en_US.UTF8"));
    std::cout.imbue(loc);
    std::cout << "\"C\" locale with en_US numpunct: " << number << '\n';
}