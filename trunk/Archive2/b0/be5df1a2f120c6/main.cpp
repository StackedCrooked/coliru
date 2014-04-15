#include <iostream>
#include <array>

int main() {
    std::array<std::array<int, 100>, 100> matrix;
    auto& ar = matrix[0];
    matrix[0][0] = 1;
    ar[0] = 2;
    std::cout << matrix[0][0] << '\n';
    std::cout << ar[0] << '\n';
}
