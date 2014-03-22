#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>


int main() {
    std::vector<int> v = { 1, 2, 3, 4, 5, 6 };
    
    int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(std::begin(v), std::end(v), std::default_random_engine(seed));
}