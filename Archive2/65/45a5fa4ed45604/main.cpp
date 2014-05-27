#include <iostream>
#include <vector>

int main() {
    try {
        std::vector<std::vector<double>> vec(5000000, std::vector<double>(5000000));
    } catch (std::bad_alloc const& e) {
        std::cout << "Opps";
    }
}
