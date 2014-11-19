#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

int main()
{
    // Vector has 8 elements.
    std::vector <int> v1 { 0, 0, 0, 1, 2, 3, 4, 5 };
    // Copy last 5 to the begin of the vector. copy_backward SegFs here.
    std::copy (v1.cbegin () + 3, v1.cend (), v1.begin ());
    assert ((v1 == std::vector <int> {1, 2, 3, 4, 5, 3, 4, 5}));
}
