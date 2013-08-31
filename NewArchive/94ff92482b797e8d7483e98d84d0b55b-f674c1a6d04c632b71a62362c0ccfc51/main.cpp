#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>


struct compare_first_only {
    template<typename T1, typename T2>
    bool operator()(const std::pair<T1, T2>& p1, const std::pair<T1, T2>& p2) {
        return p1.first < p2.first;
    }
};


int main() {
    std::vector<std::pair<int, int>> v = {
        {15,2}, {15, 1}, {2,3}, {2,1}, {7,13}, {1,10}
    };
    
    std::cout << "Original:" << std::endl;
    for(const auto& p : v) {
        std::cout << p.first << ", " << p.second << std::endl;
    }
    
    std::stable_sort(v.begin(), v.end(), compare_first_only());
    
    std::cout << std::endl << "Sorted:" << std::endl;
    for(const auto& p : v) {
        std::cout << p.first << ", " << p.second << std::endl;
    }
}