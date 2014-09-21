#include <numeric>
#include <vector>
#include <iostream>
#include <functional>
 
int main()
{
    std::vector<int> v{2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
    std::adjacent_difference(v.begin(), v.end(), v.begin());
 
    for (auto n : v) {
        std::cout << n << ' ';
    }
    std::cout << '\n';
 
    v = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    std::adjacent_difference(v.begin(), v.end() - 1, v.begin() + 1, std::plus<int>());
 
    for (auto n : v) {
        std::cout << n << ' ';
    }
    std::cout << '\n';
}