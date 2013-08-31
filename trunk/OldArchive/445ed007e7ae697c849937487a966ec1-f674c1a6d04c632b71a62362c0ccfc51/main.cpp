#include <algorithm>
#include <vector>
#include <iostream>

int main() {
    std::vector<std::vector<int>> v = {{1,2,3,4}, {5,6,7,8}, {9,10,11,12}};
    auto it = std::find(v.begin(), v.end(), std::vector<int>{5,6,7,8});
    for(auto&& i : *it) {
        std::cout << i << ' ';
    }
}