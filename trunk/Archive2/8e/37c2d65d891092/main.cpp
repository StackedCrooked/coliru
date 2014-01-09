#include <random>
#include <functional>

struct X {
    std::mt19937 generator;
    std::uniform_int_distribution<unsigned> distribution;
    decltype(std::bind(distribution, generator)) dice;

    X() : dice{std::bind(distribution, generator)} {}
};

int main() {
    X x;
    x.dice();
}