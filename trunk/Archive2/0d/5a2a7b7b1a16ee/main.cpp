#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

int find_max(int i) {
    return i;
}

template <typename T>
int find_max(const std::vector<T>& v) {
    return std::accumulate(std::begin(v), std::end(v), std::numeric_limits<int>::min(),
        [] (const int prev, const auto& v) {
            int m = find_max(v);
            return (m > prev) ? m : 0;
        });
}

int main() {
    std::vector<int> v1{1, 2, 3};
    std::vector<std::vector<int>> v2{{1, 2, 3}, {4, 5, 6}};
    std::vector<std::vector<std::vector<int>>> v3{{{1, 2, 3}, {4, 5, 6}}, {{7, 8, 9}, {10, 11, 12}}};

    std::cout << find_max(v1) << std::endl;
    std::cout << find_max(v2) << std::endl;
    std::cout << find_max(v3) << std::endl;
}