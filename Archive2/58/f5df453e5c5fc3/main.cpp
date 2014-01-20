#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>

void echo() {
    std::cout << "Echoooo";
}

int main() {
    auto x = []() { echo(); };
    x();
    return 0; 
}