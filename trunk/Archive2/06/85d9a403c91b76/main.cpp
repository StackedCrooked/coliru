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
    std::vector <int> v1 { 1, 2, 3, 2, 5, 2, 7, 2, 9 };
    std::vector <int> v2 (5);
    std::remove_copy (v1.cbegin (), v1.cend (), v2.begin (), 2);
    assert ((v2 == std::vector <int> { 1, 3, 5, 7, 9 }));
    
    auto it = std::remove_copy_if (v2.cbegin (), v2.cend (), v1.begin (), [] (int i) { return i <= 5; });
    v1.erase (it, v1.end ());
    assert ((v1 == std::vector <int> { 7, 9 }));
}
