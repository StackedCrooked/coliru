#include <iostream>

template<typename T, size_t N, size_t M>
void f(const T (&arr)[N][M]) {
    for(size_t i = 0; i < N; ++i) {
        for(size_t j = 0; j < M; ++j) {
            std::cout << arr[i][j] << ' ';
        }
        std::cout << '\n';
    }
}

int main() {
    int g[][4] = {{1,2,3,4}, {5,6,7,8}, {9,10,11,12}};
    f(g);
}