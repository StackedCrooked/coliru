#include <iostream>
#include <iomanip>

int main() {
    std::cout << std::fixed
              << 2348902348.2423948 + 23478234.092834 << '\n'
              << 2348902348.2423948f + 23478234.092834f << '\n';
}
