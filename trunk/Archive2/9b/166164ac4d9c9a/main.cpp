#include <iostream>

template <typename T, size_t N, size_t M>
void print(T (&arr)[N][M]) {
    for (size_t i = 0ul; i<N; ++i) {
        for (size_t j = 0ul; j<M; ++j)
            std::cout << arr[i][j] << " ";
        std::cout << "\n";
    }
}

int main() {
    int a[][3] = {
        { 1,2,3 },
        { 4,5,6 },
    };

    print(a);
}
