#include <iostream>

size_t test(const size_t& num) {
    std::cout << "Const...\n";
    return num;
}

size_t test(size_t& num) {
    num += 1;
    std::cout << "Non-const..\n";
    return num;
}

int main() {
    const int i = 100;
    size_t n = test(i);
    auto m = test(n);
}