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
    srand (time (0));

    // Wypisz 6 liczb z zakresu [0, 5]
    std::generate_n (std::ostream_iterator <int> (std::cerr, ","), 6, std::bind (std::modulus <int> (), std::bind (rand), 6));
    
    std::vector <int> v (6);
    int i = 0;
    std::generate (v.begin (), v.end (), [&i] () { return ++i; });
    assert ((v == std::vector <int> {1, 2, 3, 4, 5, 6}));
}
