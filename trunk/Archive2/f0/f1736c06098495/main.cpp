#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

int main() {
    using Map = std::unordered_multimap<int, int>;
    auto m = Map { {1, 1}, {1, 2}, {1, 3}, {2, 4}, {2, 5}, {3, 6} };
    
    std::vector<int> v;
    v.reserve(m.size());
    
    std::transform(begin(m), end(m), std::back_inserter(v), [](auto const& elem) {
        return elem.second;    
    });

    for (auto elem : v)
        std::cout << elem << "\n";
}
