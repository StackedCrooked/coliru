#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <cassert>
#include <iterator>
#include <cstdlib>

int main()
{
    std::vector <std::string> v1 { "ala", "ma", "kota" };
    std::vector <std::string> v2 { "centrala", "sra", "psa" };
     
    // Wszystkie 3 kolekcje są inne
    std::swap_ranges (v1.begin (), v1.end (), v2.begin ());    
    assert ((v2 == std::vector <std::string> { "ala", "ma", "kota" }));
    assert ((v1 == std::vector <std::string> { "centrala", "sra", "psa" }));
}
