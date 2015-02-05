#include <iostream>
#include <sstream>

int main()
{
    std::stringstream ss(" P");
    char c;
    ss >> std::noskipws >> c;
    std::cout << std::boolalpha << "c == ' ': " << (c == ' ');
}