#include <iostream>
#include <unordered_map>
#include <vector>

int main() {
    using Map = std::unordered_multimap<int, int>;
    auto m = Map { {1, 1}, {1, 2}, {1, 3}, {2, 4}, {2, 5}, {3, 6} };
    
    std::vector<int> v;
    v.reserve(m.size());
    
    for (auto const& elem : m)
        v.push_back(elem.second);

    for (auto const& elem : v)
        std::cout << elem << "\n";
}
