#include <iostream>
#include <sstream>
#include <iomanip>
int main()
{
    std::cout << "Parsing string \"10 0x10 010\"\n";
 
    int n1, n2, n3;
    std::istringstream s("10 0x10 010");
    s >> std::setbase(16) >> n1 >> n2 >> n3;
    std::cout << "hexadecimal parse: " << n1 << ' ' << n2 << ' ' << n3 << '\n';
 
    s.clear();
    s.seekg(0);
    s >> std::setbase(0) >> n1 >> n2 >> n3;
    std::cout << "prefix-dependent parse: " << n1 << ' ' << n2 << ' ' << n3 << '\n';
 
    std::cout << "hex output: " << std::setbase(16)
              << std::showbase << n1 << ' ' << n2 << ' ' << n3 << '\n';
}