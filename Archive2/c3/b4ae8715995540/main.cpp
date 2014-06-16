#include <iostream>
#include <memory>

template<int N>
constexpr int factorial() {
    return N * factorial<N - 1>();
}

template<>
constexpr int factorial<0>() {
    return 1;
}

int main (int argc, char ** argv) {
    std::cout << factorial<4>();
}