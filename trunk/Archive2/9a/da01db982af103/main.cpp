#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>

int half(int x) { return x / 2; }

int main() {
    std::vector<int> test(5);
    std::transform(test.begin(), test.end(), test.begin(), [](int) { return half(4); });
    return 0; 
}