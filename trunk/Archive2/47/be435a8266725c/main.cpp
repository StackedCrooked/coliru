#include <vector>
#include <algorithm>
#include <iostream>

struct Compare {
    
    Compare() {}
    
    Compare(Compare const&) {
        std::cout << "Copied\n";
    }
    
    Compare(Compare&&) {
        std::cout << "Moved\n";
    }
    
    bool operator()(int a, int b) {
        return a < b;
    }
    
};

int main() {
    std::vector<int> vec = {1, 4, 2, 8, 5, 3};
    std::sort(vec.begin(), vec.end(), Compare());
    for (int i : vec)
        std::cout << i;
}