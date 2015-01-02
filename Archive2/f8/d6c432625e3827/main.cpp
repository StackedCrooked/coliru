#include <algorithm>
#include <iostream>

constexpr int x(
    int a, int b, 
    int c, int d
) {
    return std::min({ a * c, a * d, b * c, b * d});
}

template<int A, int B, int C, int D>
auto func() {
    return x(A, B, C, D);
}

int main() {
    std::cout << func<-2, 5, 2, 4>();
}