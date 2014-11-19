#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

int main()
{
    // Vector has 8 elements. But this time last 3 are "empty"
    std::vector <int> v1 { 1, 2, 3, 4, 5, 0, 0, 0 };
    // Copy first 5 to the the end. 
    std::copy_backward (v1.cbegin (), v1.cbegin () + 5, v1.end ());
    assert ((v1 == std::vector <int> {1, 2, 3, 1, 2, 3, 4, 5}));
}
