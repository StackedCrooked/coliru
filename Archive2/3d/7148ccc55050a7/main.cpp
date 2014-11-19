#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <iterator>

int main()
{
    std::vector <int> v1 { 1, 2, 3, 4, 5 };
    v1.resize (10);    
    std::copy (v1.cbegin (), v1.cbegin () + 5, v1.begin () + 5);
    assert ((v1 == std::vector <int> {1, 2, 3, 4, 5, 1, 2, 3, 4, 5}));

    // Wyczyść 5 ostatnich liczb
    std::fill (v1.begin () + 5, v1.end (), 0);
    std::copy_backward (v1.cbegin (), v1.cbegin () + 5, v1.end ());
    assert ((v1 == std::vector <int> {1, 2, 3, 4, 5, 1, 2, 3, 4, 5}));
}
