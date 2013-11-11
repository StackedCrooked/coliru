#include <algorithm>
#include <functional>
#include <iterator>
#include <random>

int main() {
    int pointX[10];
    int pointY[10];

    std::mt19937 prng{std::random_device()()};
    std::uniform_int_distribution<> dist(1, 50);

    std::generate(std::begin(pointX), std::end(pointX), std::bind(dist, prng));
    std::generate(std::begin(pointY), std::end(pointY), std::bind(dist, prng));

    return 0;
}
