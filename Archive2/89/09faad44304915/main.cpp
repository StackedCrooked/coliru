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
    std::vector <int> v (5);
    std::iota (v.begin (), v.end (), 0);
    std::replace (v.begin (), v.end (), 1, 0);
    // 1 zamieniła się na 0
    assert ((v == std::vector <int> {0, 0, 2, 3, 4}));

    // Zamień nieparzyste na liczbę 17.
    std::replace_if (v.begin (), v.end (), std::bind (std::modulus <int> (), std::placeholders::_1, 2), 17);
    assert ((v == std::vector <int> {0, 0, 2, 17, 4}));    
}
