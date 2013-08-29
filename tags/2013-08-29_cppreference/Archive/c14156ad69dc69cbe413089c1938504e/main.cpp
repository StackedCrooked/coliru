#include <iostream>
#include <limits>

int main() {
    int const& x = std::numeric_limits<int>::digits;
    std::cout << x << "\n";
}