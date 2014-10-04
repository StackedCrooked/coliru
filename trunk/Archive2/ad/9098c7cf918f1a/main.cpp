#include <iostream>
#include <sstream>
#include <locale>
 
int main()
{
    std::istringstream iss;
    iss.imbue(std::locale("en_US.UTF8"));
 
    std::cout << "Current locale: " << iss.getloc().name() << '\n';
 
    iss.imbue(std::locale());
    std::cout << "Global locale : " << iss.getloc().name() << '\n';
}