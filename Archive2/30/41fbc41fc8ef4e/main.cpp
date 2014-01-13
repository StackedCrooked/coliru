#include <string>
#include <algorithm>
#include <iostream>
#include <array>
#include <bitset>

int main() {
    constexpr int M = 3;
    constexpr int N = 3;
    std::array<int, M * N> array = {{
        1, 2, 3,
        0, 0, 5,
        4, 2, 1
    }};
    
    std::bitset<N> zeroed_cols; 
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            int elem = array[i * N + j];
            if (elem == 0 && !zeroed_cols[j]) {
                for (int a = 0; a < M; ++a)
                    array[a * N + j] = 0;
                for (int b = 0; b < N; ++b)
                    array[i * N + b] = 0;
                zeroed_cols[j] = true;
                break;
            }
        }
    }
    
    for (int i = 0; i < M * N; ++i) {
        std::cout << array[i];
        if ((i + 1) % 3 == 0)
            std::cout << '\n';
    }

    return 0; 
}