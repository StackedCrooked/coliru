#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <map>
#include <array>
#include <algorithm>

int main() {
    std::vector<int> x;
    x.push_back(1);
    x.push_back(2);
    x.push_back(3);
    
    std::array<int, 3> y;
    std::copy(x.begin(), x.end(), y.begin());
}