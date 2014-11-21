#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <cassert>

int main()
{
    std::vector <std::string> v1 { "ala", "ma", "kota", "a", "janek", "ma", "psa" };
    std::list <std::string> v2 (v1.size ());

    std::move (v1.cbegin (), v1.cend (), v2.begin ());
    assert ((v2 == std::list <std::string> { "ala", "ma", "kota", "a", "janek", "ma", "psa" }));
}
