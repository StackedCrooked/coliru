#include <iostream>
#include <string>
#include <sstream>

int main()
{
    std::string hex = "42 6F 6F 6B 20 6F 66 20 53 75 6D 6D 6F 6E 69 6E 67";
    
    std::istringstream iss(hex);
    int i;
    while (iss >> std::hex >> i)
        std::cout << char(i);
}