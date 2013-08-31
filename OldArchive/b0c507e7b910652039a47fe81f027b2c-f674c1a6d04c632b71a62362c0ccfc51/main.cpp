#include <algorithm>
#include <vector>
#include <iostream>

int main() {
    std::vector<int> v = {1,2,3,4, 5,6,7,8, 9,10,11,12};
    std::vector<int> b{5,6,7,8};
    auto it = std::search(v.begin(), v.end(), b.begin(), b.end());
    std::cout << *it << std::endl; // prints 5
    std::cout << std::distance( v.begin(), it  ) << std::endl; // prints 4
}