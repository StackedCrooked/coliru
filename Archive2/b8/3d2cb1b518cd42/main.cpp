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
    std::list <std::string> v2 (v1.size ());

    // Transformacja z jednej do drugiej
    std::transform (v1.cbegin (), v1.cend (), v2.begin (), [] (std::string const &s) { return "[" + s + "]"; });    
    assert ((v2 == std::list <std::string> { "[ala]", "[ma]", "[kota]" }));

    // Transformacja z siebie samej do siebie samej
    std::transform (v1.cbegin (), v1.cend (), v1.begin (), [] (std::string const &s) { return "(" + s + ")"; });    
    assert ((v1 == std::vector <std::string> { "(ala)", "(ma)", "(kota)" }));
}
