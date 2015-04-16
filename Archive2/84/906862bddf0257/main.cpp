#include <algorithm>
#include <iostream>

template<typename T, std::size_t N, std::size_t M>
auto bi_begin(T (&arr)[N][M]) {
    return std::addressof(arr[0][0]);
}

template<typename T, std::size_t N, std::size_t M>
auto bi_end(T (&arr)[N][M]) {
    return bi_begin(arr) + N * M;
}

int main() {
    int arr[2][2] = {{434, 43}, {9826, 2}};
    auto pair = std::minmax_element(bi_begin(arr), bi_end(arr));
    std::cout << *pair.first << "/" << *pair.second;
}