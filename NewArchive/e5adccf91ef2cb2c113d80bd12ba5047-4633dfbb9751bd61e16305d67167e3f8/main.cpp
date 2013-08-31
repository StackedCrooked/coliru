
#include <iostream>
#include <array>
#include <algorithm>

int main() {
    std::array<int, 8> arr { 3, 5, 4, 1, 2, 7, 6, 8 };
    std::array<int*, 8> p_arr;
    
    for (unsigned i = 0; i < 8; ++i) {
        p_arr[i] = &arr[i];
    }
    
    std::sort(p_arr.begin(), p_arr.end(), [](int* a, int* b) { return *a < *b; });
    
    for (auto i : p_arr) 
        std::cout << *i;
}