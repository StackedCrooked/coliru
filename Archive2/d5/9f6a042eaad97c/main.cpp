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
    std::vector <int> v (3);
    std::fill (v.begin (), v.end (), 7);
    assert ((v == std::vector <int> {7, 7, 7}));

    std::fill_n (std::back_inserter (v), 2, 8);
    assert ((v == std::vector <int> {7, 7, 7, 8, 8}));

    // 3 razy tak.
    std::fill_n (std::ostream_iterator <std::string> (std::cerr, ","), 3, "tak");
}
