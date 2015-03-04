#include <algorithm>
#include <vector>
#include <iostream>

    template<typename ForwardIt, typename T>
    bool has_in_range(ForwardIt first, ForwardIt last, const T& i, const T& j) {
        auto lb = std::lower_bound(first, last, i);
        return lb != last && !(j < *lb);
    }
    
int main() {
    std::vector<int> v = {1, 3, 5, 10};
    std::cout << has_in_range(v.begin(), v.end(), 1, 2) << std::endl;
    std::cout << has_in_range(v.begin(), v.end(), 2, 2) << std::endl;
    std::cout << has_in_range(v.begin(), v.end(), 2, 3) << std::endl;
    std::cout << has_in_range(v.begin(), v.end(), 2, 4) << std::endl;
    std::cout << has_in_range(v.begin(), v.end(), 9, 10) << std::endl;
    std::cout << has_in_range(v.begin(), v.end(), 9, 11) << std::endl;
    std::cout << has_in_range(v.begin(), v.end(), 10, 11) << std::endl;
    std::cout << has_in_range(v.begin(), v.end(), 11, 11) << std::endl;
}