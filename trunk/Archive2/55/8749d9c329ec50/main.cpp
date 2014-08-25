#include <iostream>
#include <map>
#include <string>

std::map<std::string, std::string> element_name =
{
    { "?", "unknown"},
    { "H", "hydrogen"}
};

std::map<std::string, double> covalent_radius = 
{
    { "?", 0.85},
    { "H", 0.37}
};

int main() 
{
    std::cout << element_name["H"] << "\n";
    std::cout << covalent_radius["?"] << "\n";
}
