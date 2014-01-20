#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    int fixed_value = 42;
    std::vector<std::vector<int>> vec(4, std::vector<int>(4, fixed_value));
    
    for (const auto& v : vec)
        for (auto i : v)
            std::cout << i << ' ';
}