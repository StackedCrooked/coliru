#include <cstddef>
#include <cstdint>
#include <limits>
#include <queue>
#include <random>
#include <stdexcept>
#include <string>
#include <type_traits>

using seed_t = std::uint32_t;

template<typename T>
class integer_generator {
public:
    static_assert(std::is_integral<T>());

    integer_generator(seed_t seed)
        : prng(seed), dist(std::numeric_limits<T>::min(), std::numeric_limits<T>::max()) {
        edge_cases.emplace(0);
        for (T x = 1; x <= 5; ++x) {
            edge_cases.emplace(x);
            edge_cases.emplace(-x);
        }
        for (T x = 0; x <= 5; ++x) {
            edge_cases.emplace(std::numeric_limits<T>::min() + x);
            edge_cases.emplace(std::numeric_limits<T>::max() - x);
        }
    }

    T operator()() {
        if (!edge_cases.empty()) {
            auto result = edge_cases.front();
            edge_cases.pop();
            return result;
        } else {
            return dist(prng);
        }
    }

private:
    std::mt19937_64 prng;
    std::uniform_int_distribution<T> dist;
    std::queue<T> edge_cases;
};

template<typename G, typename F>
void verify(G&& generator, F&& property, std::size_t n = 100) {
    for (decltype(n) i = 0; i < n; ++i) {
        auto value = generator();
        if (!property(value)) {
            using std::to_string;
            throw std::runtime_error("verification failed after " + std::to_string(i) + " attempts for input " + std::to_string(value));
        }
    }
}

// example:
#include <iostream>

int main() {
    verify(integer_generator<int>(0), [] (auto n) { return n * 2 == n + n; });
    return 0;
}