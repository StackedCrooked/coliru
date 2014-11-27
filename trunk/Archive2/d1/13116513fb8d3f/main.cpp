#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <cassert>
#include <iterator>

template <typename Collection>
void reverse (Collection &c)
{
    int s = c.size () / 2;
    std::swap_ranges (c.begin (), c.begin () + s, c.rbegin ());
}

int main()
{
    std::vector <std::string> v1 { "ala", "ma", "kota" };
    reverse (v1);
    assert ((v1 == std::vector <std::string> { "kota", "ma", "ala" }));
}
