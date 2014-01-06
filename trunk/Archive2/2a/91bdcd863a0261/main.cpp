#include <iostream>

template<typename T>
using alias = T;

template<typename T, size_t N>
void f(alias<const T[N]>& x) {
    std::cout << N << '\n';
}

int main() {
    alias<int[]> x = {1,2,3,4,5};
    f(x);
}