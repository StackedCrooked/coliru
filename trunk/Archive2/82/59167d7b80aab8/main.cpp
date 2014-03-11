#include <vector>
#include <iostream>

int main() {
    std::vector<int> v1{1,2,3,4};
    std::vector<int> v2;
    
    v2.emplace_back(v1[0]);
    v2.push_back(v1[1]);
    
    for(auto const& v : v2) {
        std::cout << v << '\n';
    }
}
