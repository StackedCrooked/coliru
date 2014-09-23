#include <sstream>
#include <iostream>
#include <iomanip>
 
int main()
{
    std::cout << "pas de setw:" << 42 << "-" << 8 << '\n';
    std::cout << "avec setw:" << 42 << "-" << std::setfill('0') << std::setw(3) << 8;
}