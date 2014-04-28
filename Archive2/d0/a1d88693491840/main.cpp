#include <algorithm>
#include <iostream>
#include <vector>

std::vector<int> sum(int groups, const std::vector<int> &v) {
    std::vector<int> s;
    size_t beg = 0;
    const int g = groups;
    
    for (size_t len = v.size(); groups < len; groups += g) {
        s.push_back(std::accumulate(v.begin() + beg, v.begin() + groups, 0));
        beg = groups;
    }
    
    if (beg < v.size())
        s.push_back(std::accumulate(v.begin() + beg, v.end(), 0));
    return s;
}

int main() {
    std::vector<int> v = {89, 49, 28, 73, 93, 62, 74, 26, 57, 23};
    v = sum(5, v);
    for (auto n : v) {
        std::cout << n << " ";
    }
    return 0;
}