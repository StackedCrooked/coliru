#include <algorithm>
#include <vector>
#include <iostream>

int main() {
    std::vector<int> v = {1,2,3,4, 5,6,7,8, 9,10,11,12};
    auto it = std::find(v.begin(), v.end(), std::vector<int>{5,6,7,8});
    std::cout << *it << std::endl; // prints 5
    std::cout << std::distance( it, v.begin() ) << std::endl; // prints 5
}