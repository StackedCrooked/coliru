#include <iostream>
#include <string>
#include <tuple>
#include <vector>

static auto periodic_table = std::vector<std::tuple<std::string, std::string, double>> 
{
    std::make_tuple("?", "Unknown", 0.85),
    std::make_tuple("H", "Hydrogen", 0.37)
};

std::string element_symbol(int neutrons)
{
    return std::get<0>(periodic_table[neutrons]);    
}

std::string element_name(int neutrons)
{
    return std::get<1>(periodic_table[neutrons]);    
}

double covalent_radius(int neutrons)
{
    return std::get<2>(periodic_table[neutrons]);    
}

int main() 
{
    std::cout << element_symbol(1) << "\n";
    std::cout << element_name(1) << "\n";
    std::cout << covalent_radius(1) << "\n";
}
