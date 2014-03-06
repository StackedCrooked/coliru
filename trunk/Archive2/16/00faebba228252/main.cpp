#include <iostream>

template <typename T, size_t N>
void foo(T array[N]) {
    std::cout << N;
}

int main() {
    int array[] { 1, 2, 3, 4, 5 };
    foo(array);
}
