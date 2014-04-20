#include <iostream>

constexpr int Partition(const int n, int current) {
    return (current == 0) ? 0 : (n == 0) ? 1 : (n < 0) ? 0 :Partition(n, current - 1) + Partition(n - current, current);
}

int main() {
    std::cout << Partition(100, 100) - 100 << std::endl;
}