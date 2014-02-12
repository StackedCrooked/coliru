#include <iostream>

template <typename T>
T foo(T a, T b) {
    return a + b;
}

int main() {
   std::cout << foo(1, 4);
}