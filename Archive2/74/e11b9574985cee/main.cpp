#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <map>
#include <array>
#include <algorithm>

int main() {
    int n = 2;
    std::vector<int> x {1, 2, 3};
    std::array<int, 2> y;
    std::copy(x.begin(), x.begin() + n, y.begin());
    
    for (auto i : y) std::cout << i;
}