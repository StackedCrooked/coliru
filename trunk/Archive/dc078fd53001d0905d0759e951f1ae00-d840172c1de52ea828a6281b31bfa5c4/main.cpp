#include <iostream>

template<typename T, size_t N>
void print(const T(&array)[N]) {
    for(size_t i = 0; i < N; ++i)
        std::cout << array[i] << ' ';
}

int main() {
    int a[] = {1,2,3,4,5,6};
    print(a);
}