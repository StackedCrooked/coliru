#include <iostream>

int main() {
    alignas(2) char array[4] alignas(16), c, d alignas(4);
    std::cout << alignof(array[0]) << '\n'
              << alignof(array) << '\n'
              << alignof(c) << '\n'
              << alignof(d) << '\n';
}
