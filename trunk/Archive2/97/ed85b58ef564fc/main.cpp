#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <map>
#include <array>
#include <algorithm>

int main() {
    std::vector<int> x {1, 2, 3};
    std::array<int, 3> y;
    std::move(x.begin(), x.end(), y.begin());
    
    for (auto i : y) std::cout << i;
}