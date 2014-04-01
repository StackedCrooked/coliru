#include <memory>
#include <vector>
#include <algorithm>
#include <iostream>

int main() {
    std::vector<std::unique_ptr<int>> vec;
    vec.emplace_back(new int(7));
    vec.emplace_back(new int(8));
    vec.emplace_back(new int(9));
    vec.emplace_back(new int(10));
    vec.emplace_back(new int(11));
    vec.emplace_back(new int(12));
    
    bool remove_10 = true;
    vec.erase(std::remove_if(std::begin(vec), std::end(vec), [&](std::unique_ptr<int> const& x) {
        return remove_10 && x && *x == 10;
    }), std::end(vec));
    for(auto&& i : vec) {
        std::cout << *i << '\n';
    }
}