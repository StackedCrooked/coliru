#include <array>
#include <iostream>
#include <random>
#include <stdlib.h>

const int n_iterations = 100000000;
const int range = 20;
using histogram = std::array<unsigned, range>;

histogram fill_rand() {
    auto result = histogram{{}};
    for (int i = 0; i < n_iterations; ++i) {
        ++result[rand() % range];
    }
    return result;
}

histogram fill_random() {
    auto result = histogram{{}};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, range-1);
    
    for (int i = 0; i < n_iterations; ++i) {
        ++result[dis(gen)];
    }
    return result;
}

void dump(const histogram& r) {
    for (int i = 0, e = r.size(); i < e; ++i) {
        std::cout << '[' << i << "] = " << r[i] << " (" << r[i] * (100.0 / n_iterations) << "%)\n";
    }
}

int main() {
    std::cout << "rand() % n:\n";
    dump(fill_rand());
    std::cout << "\nrandom:\n";
    dump(fill_random());
    std::cout << "\nRAND_MAX: " << RAND_MAX << ", range: " << range << ", RAND_MAX % range = " << RAND_MAX % range << '\n';
}
