#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>


int main() {
    std::vector<std::pair<int, int>> v = {
        {15,2}, {3,3}, {8,1}, {7,13}, {1,10}
    };
    
    std::cout << "Original:" << std::endl;
    for(const auto& p : v) {
        std::cout << p.first << ", " << p.second << std::endl;
    }
    
    std::sort(v.begin(), v.end());
    
    std::cout << std::endl << "Sorted:" << std::endl;
    for(const auto& p : v) {
        std::cout << p.first << ", " << p.second << std::endl;
    }
}