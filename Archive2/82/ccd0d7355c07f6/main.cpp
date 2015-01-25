#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

int
main() {
    std::vector<std::unique_ptr<int>> v;
    v.emplace_back(std::make_unique<int>(1));
    v.emplace_back(std::make_unique<int>(2));
    
    v.erase(std::remove_if(v.begin(), v.end(),
                           [] (std::unique_ptr<int> const& p) { return *p == 2; }),
            v.end());
    
    for (auto& p : v)
        std::cout << *p << '\n';
}
