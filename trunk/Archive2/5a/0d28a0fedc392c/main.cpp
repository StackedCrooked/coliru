#include <sstream>
#include <iostream>
#include <iomanip>
 
int main()
{
    std::cout << "no setw:" << 42 << '\n'
              << "setw(6):" << std::setw(6) << 42 << '\n'
              << "setw(6), several elements: " << 89 << std::setw(6) << 12 << 34 << '\n';
    std::istringstream is("hello, world");
    char arr[10];
    is >> std::setw(6) >> arr;
    std::cout << "Input from \"" << is.str() << "\" with setw(6) gave \""
              << arr << "\"\n";
}