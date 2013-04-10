#include <iostream>
#include <cstddef>

template<std::size_t N>
void print_n() {
    std::cout << N << ' ';
    print_n<N - 1>();
}

template<>
void print_n<0>() {
    
}

int main() {
    print_n<100>();
}
