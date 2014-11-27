#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <cassert>
#include <iterator>

int main()
{
    std::vector <std::string> v1 { "ala", "ma", "kota" };
    std::vector <std::string> v2 { "centrala", "sra", "psa" };
    std::list <std::string> v3 (v1.size ());

    // Wszystkie 3 kolekcje są inne
    std::transform (v1.cbegin (), v1.cend (), v2.cbegin (), v3.begin (), [] (std::string const &s1, std::string const &s2) { 
        return s1 + "-" + s2; });    
    assert ((v3 == std::list <std::string> { "ala-centrala", "ma-sra", "kota-psa" }));

    // Wszystkie 3 takie same
    std::vector <int> v4 { 1, 2, 3, 4, 5 };
    std::transform (v4.cbegin (), v4.cend (), v4.cbegin (), v4.begin (), std::multiplies <int> ());    
    assert ((v4 == std::vector <int> { 1, 4, 9, 16, 25 }));
}
