#include <iostream>
#include <random>

int main() {
    std::mt19937 gen{std::random_device{}()};
    std::uniform_real_distribution<> dist(0.0, 1.0);
    std::cout << dist(gen);
}