#include <algorithm>
#include <array>
#include <functional>
#include <random>

int main() {
    std::array<int, 10> pointX;
    std::array<int, 10> pointY;

    std::mt19937 prng{std::random_device()()};
    std::uniform_int_distribution<> dist(1, 50);

    std::generate(pointX.begin(), pointX.end(), std::bind(dist, prng));
    std::generate(pointY.begin(), pointY.end(), std::bind(dist, prng));

    return 0;
}
