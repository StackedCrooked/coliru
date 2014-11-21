#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

int main()
{
    std::vector <int> v1 { 1, 2, 3 };
    std::vector <int> v2 (9);

    auto it = std::copy (v1.cbegin (), v1.cend (), v2.begin ());
         it = std::copy (v1.cbegin (), v1.cend (), it);
         it = std::copy (v1.cbegin (), v1.cend (), it);
     
    assert ((v2 == std::vector <int> {1, 2, 3, 1, 2, 3, 1, 2, 3}));
}
