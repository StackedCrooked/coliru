#include <cstdint>
#include <limits>
#include <queue>
#include <random>
#include <type_traits>

using seed_t = std::uint32_t;

template<typename T>
class integer_generator {
public:
    static_assert(std::is_integral<T>());

    integer_generator(seed_t seed)
        : prng(seed), dist(std::numeric_limits<T>::min(), std::numeric_limits<T>::max()) {
        edge_cases.push(T(0));
        for (T x = 1; x <= 5; ++x) {
            edge_cases.push(x);
            edge_cases.push(-x);
        }
        for (T x = 0; x <= 5; ++x) {
            edge_cases.push(std::numeric_limits<T>::min() + x);
            edge_cases.push(std::numeric_limits<T>::max() - x);
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

// example:
#include <iostream>

int main() {
    integer_generator<int> gen(0);
    for (auto i = 0; i < 100; ++i) {
        std::cout << gen() << '\n';
    }
    return 0;
}